#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition
#include "stdlib.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sphere.h"
#include "surface_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    blue = .02;
    connect(ui->pushButton, SIGNAL(pressed()),
            this, SLOT(raytrace()));
    connect(ui->blue_slide, SIGNAL(sliderMoved(int)),
            this,SLOT(updateBlue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//determines the color of a pixel
vec3 color(const ray& r, surface *world, int depth)
{
    hit_record rec;
    int max_depth = 20;
//    if(world->hit((r,0.0, MAXFLOAT, rec))
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

void MainWindow::raytrace()
{
    QString filename = "traceout.ppm";
    QFile file( filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );

        int nx = ui->widget->width();
        int ny = ui->widget->height();

        surface *list[4];
        list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.2,0.5,0.8)));
        list[1] = new sphere(vec3(0,-100.5,-1.5),100,new lambertian(vec3(0.2,0.8,0.3)));
        list[2] = new sphere(vec3(1,0,-1),0.5,new metal(vec3(0.2,0.5,0.4)));
        list[3] = new sphere(vec3(-1,0,-1),0.5,new metal(vec3(0.5,0.5,0.5)));
        surface_list *world = new surface_list(list,4);

        camera cam;

        //setup header for PPM file
        stream << "P3\n" << nx << " " << ny << "\n255\n";

        for(int j = ny -1; j >= 0; j--)
        {
            for(int i = 0; i <nx; i++)
            {

                int aa_samples = 50;
                vec3 col(0,0,0);
                for(int g = 0; g < aa_samples; g++)
                {

                    srand(j*i*g);
                    float u = (float(i + (float)rand()/(float)RAND_MAX)) / float(nx);
                    float v = (float(j + (float)rand()/(float)RAND_MAX)) / float(ny);
//                    if(i == 10 && j == 10)
//                        std::cout << "u: " << u << "  ";
                    ray r = cam.get_ray(u,v);
                    vec3 p   = r.point_at_parameter(2.0);
                    col += color(r,world,0);

                }
//                if(i == 10 && j == 10)
//                    std::cout << std::endl;
//                std::cout << std::endl;
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



void MainWindow::updateBlue(int new_blue)
{
    blue = float(new_blue)/100;
}
