#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition
#include "stdlib.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sphere.h"
#include "moving_sphere.h"
#include "surface_list.h"
#include "bvh_node.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "utilities.h"

//===================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(pressed()),
            this, SLOT(raytrace()));
}

//===================================================================
MainWindow::~MainWindow()
{
    delete ui;
}
//===================================================================
//determines the color of a pixel
vec3 color(const ray& r, surface *world, int depth)
{
    hit_record rec;
    int max_depth = 20;
    if(world->hit(r,0.0001, FLT_MAX, rec))
    {
        ray scattered;
        vec3 attenuation;
        if(depth < max_depth && rec.mat_ptr->scatter(r,rec,attenuation,scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0,0,0);
        }
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() +1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);
    }
}

//===================================================================
void MainWindow::raytrace()
{
    QString filename = "traceout.ppm";
    QFile file( filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );

        int nx = ui->widget->width();
        int ny = ui->widget->height();

        int number_of_balls = ui->num_diffuse->value()
                            + ui->num_glass->value()*2
                            + ui->num_metal->value();

        surface *list[number_of_balls];
        //surface_list *world = new surface_list(list,number_of_balls);
        list[0] = new sphere(vec3(0,-100.5,-1),100,
                                     new lambertian(vec3(0.2,0.8,0.3)));
        int i = 1;
        /*for(int j = i; j < 5; ++j)
        {
            vec3 location((((float)rand()/(float)RAND_MAX)-.5)*4,
                          (((float)rand()/(float)RAND_MAX)-.5)*4,
                          (((float)rand()/(float)RAND_MAX)-.5)*4);
            vec3 location2((((float)rand()/(float)RAND_MAX)-.5)*4,
                          (((float)rand()/(float)RAND_MAX)-.5)*4,
                          (((float)rand()/(float)RAND_MAX)-.5)*4);
            vec3 color((float)rand()/(float)RAND_MAX,
                       (float)rand()/(float)RAND_MAX,
                       (float)rand()/(float)RAND_MAX);
            list[i] = new moving_sphere(location,location2, 0.5, 0, 1,
                                        new lambertian(color));
            ++i;
        }*/

        //add difuse
        int next_max = ui->num_diffuse->value();
        while(i <= next_max)
        {
            vec3 color((float)rand()/(float)RAND_MAX,
                       (float)rand()/(float)RAND_MAX,
                       (float)rand()/(float)RAND_MAX);

            if(ui->checkBox->isChecked())
            {
                //use motion
                vec3 location((((float)rand()/(float)RAND_MAX)-.5)*4,
                              (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                              (((float)rand()/(float)RAND_MAX)-.5)*4);
                vec3 location2((((float)rand()/(float)RAND_MAX)-.5)*4,
                              (((float)rand()/(float)RAND_MAX)-.5)*0.5,
                              (((float)rand()/(float)RAND_MAX)-.5)*4);
                list[i] = new moving_sphere(location,location2, 0.5, 0, 1,
                                            new lambertian(color));
            }
            else
            {
                vec3 location((((float)rand()/(float)RAND_MAX)-.5)*4,
                              (((float)rand()/(float)RAND_MAX)-.5)*4,
                              (((float)rand()/(float)RAND_MAX)-.5)*4);

                list[i] = new sphere(location,0.5, new lambertian(color));
            }
            ++i;
        }

        //add glass spheres
        next_max = next_max + 2 * ui->num_glass->value();
        while(i <= next_max)
        {
            vec3 location;
            if(ui->checkBox->isChecked())
            {
                location= vec3((((float)rand()/(float)RAND_MAX)-.5)*4,
                               (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                               (((float)rand()/(float)RAND_MAX)-.5)*4);
            }
            else
            {
                location = vec3((((float)rand()/(float)RAND_MAX)-.5)*4,
                                (((float)rand()/(float)RAND_MAX)-.5)*4,
                                (((float)rand()/(float)RAND_MAX)-.5)*4);
            }
            list[i] = new sphere(location,0.5,
                                 new dielectric(vec3(1.0,1.0,1.0)));
            ++i;
            list[i] = new sphere(location,-0.45, new
                                 dielectric(vec3(1.0,1.0,1.0)));
            ++i;
        }

        //
        next_max = next_max + ui->num_metal->value();
        while(i <= next_max)
        {
            vec3 location;
            if(ui->checkBox->isChecked())
            {
                location= vec3((((float)rand()/(float)RAND_MAX)-.5)*4,
                               (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                               (((float)rand()/(float)RAND_MAX)-.5)*4);
            }
            else
            {
                location = vec3((((float)rand()/(float)RAND_MAX)-.5)*4,
                                (((float)rand()/(float)RAND_MAX)-.5)*4,
                                (((float)rand()/(float)RAND_MAX)-.5)*4);
            }
            vec3 color((float)rand()/(float)RAND_MAX,
                       (float)rand()/(float)RAND_MAX,
                       (float)rand()/(float)RAND_MAX);
            list[i] = new sphere(location,0.5, new metal(color));
            ++i;
        }

        bvh_node *world = new bvh_node(list,number_of_balls,0,1);


        vec3 camera_center = vec3(ui->camera_x->value(),
                                  ui->camera_y->value(),
                                  ui->camera_z->value());
        vec3 look_at       = vec3(ui->point_x->value(),
                                  ui->point_y->value(),
                                  ui->point_z->value());
        camera cam(camera_center,look_at,vec3(0,1,0),
                   90,float(nx)/float(ny),.01,(camera_center-look_at).length(),0,1);

        //setup header for PPM file
        stream << "P3\n" << nx << " " << ny << "\n255\n";

        for(int j = ny -1; j >= 0; j--)
        {
            for(int i = 0; i <nx; i++)
            {
                int aa_samples = ui->num_samples->value();
                vec3 col(0,0,0);
                for(int g = 0; g < aa_samples; g++)
                {
                    srand(j*i*g);
                    float u = (float(i + (float)rand()/(float)RAND_MAX)) / float(nx);
                    float v = (float(j + (float)rand()/(float)RAND_MAX)) / float(ny);

                    ray r = cam.get_ray(u,v);
//                    vec3 p   = r.point_at_parameter(2.0);
                    col += color(r,world,0);

                }

                col /= aa_samples;
                col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);

                stream << ir << " " << ig << " " << ib << "\n";
            }
        }
    }
    file.close();

    ui->widget->setStyleSheet("QWidget {background-image: url(./traceout.ppm) stretch;}");
}
