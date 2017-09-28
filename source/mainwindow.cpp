#include <QFile>
#include <QTextStream>
#include "iostream"
#include "float.h" // for MAXFLOAT definition
#include "stdlib.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "camera.h"
#include "raytracer.h"
//#include "surface_list.h" //DEPRECATED
//include surfaces/hitables
#include "bvh_node.h"
#include "flip_normals.h"
#include "transformation.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "xy_rect.h"
#include "xz_rect.h"
#include "yz_rect.h"
#include "box.h"
//include materials/shaders
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "utilities.h"
#include "diffuse_light.h"
//include textures
#include "texture.h"
#include "constant_texture.h"
#include "checker_texture.h"
#include "image_texture.h"
#include "noise_texture.h"

#include "constant_medium.h"

//===================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(pressed()),
            this, SLOT(raytrace()));

    world = build_cornell_box();


    raytracer = new Raytracer();
    raytracer->moveToThread(&raytrace_thread);
    connect(&raytrace_thread, &QThread::finished,
            raytracer, &QObject::deleteLater);
    connect(this, SIGNAL(raytrace_command(int,int,bvh_node*,int,float,float,float,float,float,float)),
            raytracer, SLOT(raytrace(int,int,bvh_node*,int,float,float,float,float,float,float)));
    connect(raytracer, SIGNAL(raytrace_complete()),
            this, SLOT(finish_raytrace()));
    connect(raytracer, SIGNAL(progress_update(float)),
            this, SLOT(update_progress(float)));
    raytrace_thread.start();

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
        /*vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() +1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0);*/
        return vec3(0,0,0);
    }
}

//===================================================================
void MainWindow::raytrace()
{
    /* QString filename = "traceout.ppm";
    QFile file( filename);
    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream( &file );

        int nx = ui->widget->width();
        int ny = ui->widget->height();


//        if(world!=NULL)
//            delete world;

//        world = build_checker_scene(ui->num_diffuse->value(),
//                                              ui->num_glass->value(),
//                                              ui->num_metal->value());

        if(world==NULL)
            world = build_cornell_box();

        vec3 camera_center = vec3(ui->camera_x->value(),
                                  ui->camera_y->value(),
                                  ui->camera_z->value());
        vec3 look_at       = vec3(ui->point_x->value(),
                                  ui->point_y->value(),
                                  ui->point_z->value());
//        camera cam(camera_center,look_at,vec3(0,1,0),
//                   90,float(nx)/float(ny),.01,(camera_center-look_at).length(),0,1);
        camera cam(camera_center,look_at,vec3(0,1,0),
                   40,float(nx)/float(ny),0.0,10,0,1);

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
    file.close();*/

    if(world==NULL)
        world = build_cornell_box();

    vec3 camera_loc(ui->camera_x->value(),
         ui->camera_y->value(),
         ui->camera_z->value());

    vec3 look_at       = vec3(ui->point_x->value(),
                              ui->point_y->value(),
                              ui->point_z->value());

    emit raytrace_command(ui->widget->width(),
                          ui->widget->height(),
                          world,
                          ui->num_samples->value(),
                          ui->camera_x->value(),
                          ui->camera_y->value(),
                          ui->camera_z->value(),
                          ui->point_x->value(),
                          ui->point_y->value(),
                          ui->point_z->value());

    ui->pushButton->setDisabled(true);
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

    surface *list[number_of_balls+1];
 /*   texture *large_color = new checker_texture(new constant_texture(vec3(0.15,0.3,0.1)),
                                               new constant_texture(vec3(0.9,0.9,0.9)));*/
    texture *large_color = new noise_texture();
    list[0] = new sphere(vec3(0,-100.5,-1),100,
                         new lambertian(large_color));

    list[1] = new xy_rect(3,5,1,3,-2, new diffuse_light(new constant_texture(vec3(4,4,4))));

    int i = 2; //start at one since we assume base layer/ball

    //test
    texture *image_text = new image_texture(QString("C:\\Users\\John\\Projects\\Raytracer\\test_image.jpg"));
    list[i] = new sphere(vec3(0,0,-1),1.25,new lambertian(image_text));
    ++i;
    //end test

    //add difuse/lambert
    int next_max = ui->num_diffuse->value();
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
    next_max = next_max + 2 * ui->num_glass->value();
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
    next_max = next_max + ui->num_metal->value();
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

//===================================================================
bvh_node* MainWindow::build_cornell_box()
{
    surface *list[9];
    int i = 0;

    //define materials
    material *red = new lambertian(
                new constant_texture(vec3(0.65,0.05,0.05)));
    material *white = new lambertian(
                new constant_texture(vec3(0.73,0.73,0.73)));
    material *green = new lambertian(
                new constant_texture(vec3(0.12,0.45,0.15)));
    material *light = new diffuse_light(
                new constant_texture(vec3(7,7,7)));

    //define shapes
    //left_wall
    list[0] = new flip_normals(new yz_rect(0,555,0,555,555,green));
    //right wall
    list[1] = new yz_rect(0,555,0,555,0,red);
    //light
    list[2] = new xz_rect(113,443,127,432,553,light);
    //ceiling
    list[3] = new flip_normals(new xz_rect(0,555,0,555,554,white));
    //list[4] = new xz_rect(0,555,0,555,555,white);
    list[4] =new yz_rect(0,555,0,555,556,green);
    //floor
    list[5] = new xz_rect(0,555,0,555,0,white);
    //back
    list[6] = new flip_normals(new xy_rect(0,555,0,555,555,white));

    surface* b1 = new translate(new rotate_y(new box(vec3(0,0,0), vec3(165,165,165),white), -18), vec3(130,0,65));
    surface* b2 = new translate(new rotate_y(new box(vec3(0,0,0), vec3(165,330,165),white), 15), vec3(265,0,295));
    //box 1
    list[7] = new constant_medium(b1, 0.01, new constant_texture(vec3(1.0,1.0,1.0)));
    //box 2
    list[8] = new constant_medium(b2, 0.01, new constant_texture(vec3(0.0,0.0,0.0)));
    bvh_node *new_world = new bvh_node(list,9,0,1);

    return new_world;

}

void MainWindow::finish_raytrace()
{
        ui->widget->setStyleSheet("QWidget {background-image: url(./traceout.ppm) stretch;}");

        ui->pushButton->setDisabled(false);
}

void MainWindow::update_progress(float percent)
{
    ui->progressBar->setValue(percent);
}
