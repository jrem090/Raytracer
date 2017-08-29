#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition
#include "stdlib.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "surface_list.h" //DEPRECATED
//include surfaces/hitables
#include "bvh_node.h"
#include "sphere.h"
#include "moving_sphere.h"
//include materials
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "utilities.h"
//include textures
#include "texture.h"
#include "constant_texture.h"
#include "checker_texture.h"
#include "image_texture.h"
#include "noise_texture.h"
#include "ui/scene_widget.h"
#include "ui/random_scene.h"
#include "ui/custom_scene_widget.h"

//===================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->widget_2 = new scene_widget();
    scene = new random_scene();
    scene->show();
    ui->scene_layout->addWidget(scene);
    //ui->widget_2->show();

    connect(ui->pushButton, SIGNAL(pressed()),
            this, SLOT(raytrace()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(scene_mode_changed(int)));
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

        if(world!=NULL)
            delete world;

        //world = build_checker_scene(5,5,5);
        if(scene != NULL)
        {
            world = scene->get_scene_data();
        }
        else
        {
            std::cout << "scene not connected" << std::endl;
            world = build_checker_scene(5,5,5);
        }
        /*world = build_checker_scene(ui->num_diffuse->value(),
                                              ui->num_glass->value(),
                                              ui->num_metal->value()); */

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

void MainWindow::scene_mode_changed(int new_mode)
{
    //scene->hide();
    ui->scene_layout->removeWidget(scene);
    delete scene;

    std::cout << "new_mode: " << new_mode << std::endl;

    if(new_mode == 0)
    {
        std::cout << "set random scene" << std::endl;
        scene = new random_scene();
        //scene->show();
        ui->scene_layout->addWidget(scene);
    }
    if(new_mode == 1)
    {
        std::cout << "set custom scene" << std::endl;
        scene = new custom_scene_widget();
        //scene->show();
        ui->scene_layout->addWidget(scene);
    }
}

//===================================================================
bvh_node* MainWindow::build_checker_scene(unsigned int num_diffuse,
                                          unsigned int num_glass,
                                          unsigned int num_metal)
{
    int number_of_balls = 1 + num_diffuse + num_glass*2 + num_metal;

    //test
    number_of_balls++;
    //end test

    surface *list[number_of_balls];
 /*   texture *large_color = new checker_texture(new constant_texture(vec3(0.15,0.3,0.1)),
                                               new constant_texture(vec3(0.9,0.9,0.9)));*/
    texture *large_color = new noise_texture();
    list[0] = new sphere(vec3(0,-100.5,-1),100,
                         new lambertian(large_color));

    int i = 1; //start at one since we assume base layer/ball

    //test
    texture *image_text = new image_texture(QString("C:\\Users\\John\\Projects\\Raytracer\\test_image.jpg"));
    list[i] = new sphere(vec3(0,0,-1),1.25,new lambertian(image_text));
    ++i;
    //end test

    //add difuse/lambert
    //int next_max = ui->num_diffuse->value();
    int next_max = 1+ num_diffuse;
    while(i <= next_max)
    {
        vec3 diffuse_color((float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX);
        constant_texture *color = new constant_texture(diffuse_color);


        vec3 location((((float)rand()/(float)RAND_MAX)-.5)*10,
                      (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                      (((float)rand()/(float)RAND_MAX)-.5)*10);
        vec3 location2(location.x(),
                       (location.y()+((float)rand()/
                                      (float)RAND_MAX)),
                       location.z());
        list[i] = new moving_sphere(location,location2, 0.5, 0, 1,
                                    new lambertian(color));

        ++i;
    }

    //add glass spheres
    //next_max = next_max + 2 * ui->num_glass->value();
    next_max += 2*num_glass;
    while(i <= next_max)
    {
        vec3 location = vec3((((float)rand()/(float)RAND_MAX)-.5)*10,
                             (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                             (((float)rand()/(float)RAND_MAX)-.5)*10);


        list[i] = new sphere(location,0.5,
                             new dielectric(vec3(1.0,1.0,1.0)));
        ++i;
        list[i] = new sphere(location,-0.45, new
                             dielectric(vec3(1.0,1.0,1.0)));
        ++i;
    }

    // add metal spheres
    //next_max = next_max + ui->num_metal->value();
    next_max += num_metal;
    while(i <= next_max)
    {
        vec3 location;

        vec3 color((float)rand()/(float)RAND_MAX,
                   (float)rand()/(float)RAND_MAX,
                   (float)rand()/(float)RAND_MAX);

        location= vec3((((float)rand()/(float)RAND_MAX)-.5)*10,
                       (((float)rand()/(float)RAND_MAX)-1)*0.25,
                       (((float)rand()/(float)RAND_MAX)-.5)*10);
        list[i] = new sphere(location,0.5, new metal(color));

        ++i;
    }

    bvh_node *new_world = new bvh_node(list,number_of_balls,0,1);

    return new_world;
}
