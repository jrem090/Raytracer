#include "raytracer.h"

#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition
#include "stdlib.h"

#include "bvh_node.h"
#include "camera.h"
#include "vec3.h"

#include "material.h"

//include textures
#include "texture.h"
#include "oidn/include/OpenImageDenoise/oidn.hpp"


Raytracer::Raytracer(QObject *parent) : QObject(parent)
{

}

void Raytracer::raytrace(int width, int height, bvh_node* world, int samples,
                         float cam_x, float cam_y, float cam_z,
                         float focal_x, float focal_y, float focal_z)
{
    QString filename = "traceout.ppm";
    QFile file( filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );

        int nx = width;
        int ny = height;

        vec3 camera_center = vec3(cam_x,cam_y, cam_z);
        vec3 look_at       = vec3(focal_x, focal_y, focal_z);

       camera cam(camera_center,look_at,vec3(0,1,0),
                   40,float(nx)/float(ny),0.0,10,0,1);

        //setup header for PPM file
        stream << "P3\n" << nx << " " << ny << "\n255\n";

        if(true)
        {
            float buffer[nx * ny *3];
            float output[nx * ny *3];
            for(int j = ny -1; j >= 0; j--)
            {
                for(int i = 0; i <nx; i++)
                {
                    int aa_samples = samples;
                    vec3 col(0,0,0);
                    for(int g = 0; g < aa_samples; g++)
                    {
                        srand(j*i*g);
                        float u = (float(i + (float)rand()/(float)RAND_MAX)) / float(nx);
                        float v = (float(j + (float)rand()/(float)RAND_MAX)) / float(ny);

                        ray r = cam.get_ray(u,v);
                        col += color(r,world,0);

                    }

                    col /= aa_samples;
                    col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
                    buffer[i*j*3] = col[0];
                    buffer[i*j*3+1] = col[1];
                    buffer[i*j*3+2] = col[2];
                    //int ir = int(255.99*col[0]);
                    //int ig = int(255.99*col[1]);
                    //int ib = int(255.99*col[2]);

                    //stream << ir << " " << ig << " " << ib << "\n";
                }
            }
                //intel denoise stuff
                // Create an Intel Open Image Denoise device
                oidn::DeviceRef device = oidn::newDevice();
                device.commit();

                // Create a denoising filter
                oidn::FilterRef filter = device.newFilter("RT"); // generic ray tracing filter
                filter.setImage("color",  buffer,  oidn::Format::Float3, width, height);
                //filter.setImage("albedo", albedoPtr, oidn::Format::Float3, width, height); // optional
                //filter.setImage("normal", normalPtr, oidn::Format::Float3, width, height); // optional
                filter.setImage("output", output, oidn::Format::Float3, width, height);
                filter.set("hdr", false); // image is HDR
                filter.commit();

                // Filter the image
                filter.execute();

                // Check for errors
                const char* errorMessage;
                if (device.getError(errorMessage) != oidn::Error::None)
                  std::cout << "Error: " << errorMessage << std::endl;


                for(int i = 0; i < nx; ++i)
                {
                    for (int j=0; j < ny; ++j)
                    {
                        int ir = int(255.99*output[i*j*3]);
                        int ig = int(255.99*output[i*j*3 +1]);
                        int ib = int(255.99*output[i*j*3 +2]);

                        stream << ir << " " << ig << " " << ib << "\n";
                    }
                }

        }
        else
        {
        for(int j = ny -1; j >= 0; j--)
        {
            for(int i = 0; i <nx; i++)
            {
                int aa_samples = samples;
                vec3 col(0,0,0);
                for(int g = 0; g < aa_samples; g++)
                {
                    srand(j*i*g);
                    float u = (float(i + (float)rand()/(float)RAND_MAX)) / float(nx);
                    float v = (float(j + (float)rand()/(float)RAND_MAX)) / float(ny);

                    ray r = cam.get_ray(u,v);
                    col += color(r,world,0);

                }

                col /= aa_samples;
                col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);

                stream << ir << " " << ig << " " << ib << "\n";
            }
            float percent = ((float)ny - (float)j)/(float)ny;
            emit progress_update(percent*100);
        }
        }
    }
    file.close();

    emit raytrace_complete();

}

vec3 Raytracer::color(const ray &r, surface *world, int depth)
{
    hit_record rec;
    int max_depth = 15;//change to rays?
    if(world->hit(r,0.0001, FLT_MAX, rec))
    {
        ray scattered;
        vec3 attenuation;
         //0 for non-emitting textures
        vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        if(depth < max_depth && rec.mat_ptr->
                scatter(r,rec,attenuation,scattered))
        {
            return emitted + attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return emitted;
        }
    }
    else
    {
        return vec3(0,0,0);
    }
}



