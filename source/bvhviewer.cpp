#include "bvhviewer.h"
#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition
#include "stdlib.h"

#include "camera.h"

BVHViewer::BVHViewer(QObject *parent) : QObject(parent)
{

}

void BVHViewer::bvh_trace(int width, int height, bvh_node* world, int samples,
                          float cam_x, float cam_y, float cam_z,
                          float focal_x, float focal_y, float focal_z)
{
    QString filename = "bvhout.ppm";
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

        float highest = 0;
        float counts[ny][nx];
        for(int j = ny -1; j >= 0; j--)
        {
            for(int i = 0; i <nx; i++)
            {
                //int aa_samples = ui->num_samples->value();

                int aa_samples = samples;
                vec3 col(0,0,0);
                float count = 0;
                for(int g = 0; g < aa_samples; g++)
                {
                    srand(j*i*g);
                    float u = (float(i + (float)rand()/(float)RAND_MAX)) / float(nx);
                    float v = (float(j + (float)rand()/(float)RAND_MAX)) / float(ny);

                    ray r = cam.get_ray(u,v);
                    //                    vec3 p   = r.point_at_parameter(2.0);
                    count += counter(r,world,0);

                }

                count /= aa_samples;
                if(count > highest)
                    highest = count;
                counts[j][i] = count;
            }
            float percent = ((float)ny - (float)j)/(float)ny;
            emit progress_update(percent*100 -1);
        }

        for(int j = ny -1; j >= 0; j--)
        {
            for(int i = 0; i <nx; i++)
            {

                int ir = int(255.99* counts[j][i] / highest);
                int ig = int(255.99*counts[j][i] / highest);
                int ib = int(255.99*counts[j][i] / highest);

                stream << ir << " " << ig << " " << ib << "\n";
            }
        }
         emit progress_update(100);
        file.close();

        emit bvh_complete();

    }
}

int BVHViewer::counter(const ray &r, surface *world, int depth)
{
    hit_record rec;
    //int max_depth = 15;//change to rays?
    return world->bvh_hit(r,0.0001, FLT_MAX, rec);
}
