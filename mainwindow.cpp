#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sphere.h"
#include "surface_list.h"


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
vec3 color(const ray& r, surface *world)
{
    hit_record rec;
//    if(world->hit((r,0.0, MAXFLOAT, rec))
    if(world->hit(r,0.0, FLT_MAX, rec))
    {
        return 0.5*vec3(rec.normal.x()+1,
                        rec.normal.y()+1,
                        rec.normal.z()+1);
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
        vec3 lower_left_corner (-2.0,-1.5,-1.0);
        vec3 horizontal(4.0,0,0);
        vec3 vertical(0,3.0,0);
        vec3 origin(0,0,0);
        surface *list[1];
        list[0] = new sphere(vec3(0,0,-1),0.5);
        //list[1] = new sphere(vec3(0,-100.5,-1),100);

        surface_list *world = new surface_list(list,1);

        //setup header for PPM file
        stream << "P3\n" << nx << " " << ny << "\n255\n";

        for(int j = ny -1; j >= 0; j--)
        {
            for(int i = 0; i <nx; i++)
            {

                if(j <20)
                {
                    float x = 22;
                }
                float u = float(i) / float(nx);
                float v = float(j) / float(ny);
                ray r(origin, lower_left_corner + u*horizontal+v*vertical);

                vec3 p   = r.point_at_parameter(2.0);
                vec3 col = color(r,world);
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
