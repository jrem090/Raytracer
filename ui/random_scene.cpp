//#include "../source/mainwindow.h"

//#include "surface_list.h" //DEPRECATED
//include surfaces/hitables
#include "../source/bvh_node.h"
#include "../source/sphere.h"
#include "../source/moving_sphere.h"
//include materials
#include "../source/lambertian.h"
#include "../source/metal.h"
#include "../source/dielectric.h"
#include "../source/utilities.h"
//include textures
#include "../source/texture.h"
#include "../source/constant_texture.h"
#include "../source/checker_texture.h"
#include "../source/image_texture.h"
#include "../source/noise_texture.h"
#include "../ui/scene_widget.h"
#include "ui/random_scene.h"
#include "scene_widget.h"
#include "ui/random_scene.h"
#include "ui_random_scene.h"

random_scene::random_scene(QWidget *parent) :
    scene_widget(parent),
    ui(new Ui::random_scene)
{
    ui->setupUi(this);
}

bvh_node* random_scene::get_scene_data()
{
    //find out the total number of items
    int num_items = 0;
    num_items += ui->diffuse_box->value()
            +  ui->metal_box->value()
            + (2 * ui->glass_box->value())
            + ui->image_box->value()
            + ui->checker_box->value();
    if(ui->base_check->isChecked())
        num_items++;

    //create a list for all the items
    surface *list[num_items];


    unsigned int index = 0;
    if(ui->base_check->isChecked())
    {
        texture *base_color = new noise_texture();
        list[index] = new sphere(vec3(0,-100.5,-1),100,
                         new lambertian(base_color));
        ++index;
    }


    for(int i = 0; i < ui->diffuse_box->value(); ++i)
    {
        vec3 diffuse_color((float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX);
        constant_texture *color = new constant_texture(diffuse_color);


        vec3 location((((float)rand()/(float)RAND_MAX)-.5)*10,
                      (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                      (((float)rand()/(float)RAND_MAX)-.5)*10);
        list[index] = new sphere(location,0.5, new lambertian(color));
        ++index;
    }

    for(int i = 0; i < ui->metal_box->value(); ++i)
    {
        vec3 location;

        vec3 color((float)rand()/(float)RAND_MAX,
                   (float)rand()/(float)RAND_MAX,
                   (float)rand()/(float)RAND_MAX);

        location= vec3((((float)rand()/(float)RAND_MAX)-.5)*10,
                       (((float)rand()/(float)RAND_MAX)-1)*0.25,
                       (((float)rand()/(float)RAND_MAX)-.5)*10);
        list[index] = new sphere(location,0.5, new metal(color));

        ++index;
    }

    for(int i = 0; i < ui->glass_box->value(); ++i)
    {
        vec3 location = vec3((((float)rand()/(float)RAND_MAX)-.5)*10,
                             (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                             (((float)rand()/(float)RAND_MAX)-.5)*10);


        list[index] = new sphere(location,0.5,
                             new dielectric(vec3(1.0,1.0,1.0)));
        ++index;
        list[index] = new sphere(location,-0.45, new
                             dielectric(vec3(1.0,1.0,1.0)));
        ++index;
    }

    for(int i = 0; i < ui->image_box->value(); ++i)
    {
        texture *image_text = new image_texture(QString("C:\\Users\\John\\Projects\\Raytracer\\test_image.jpg"));

        vec3 location((((float)rand()/(float)RAND_MAX)-.5)*10,
                      (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                      (((float)rand()/(float)RAND_MAX)-.5)*10);
        list[index] = new sphere(location,0.5, new lambertian(image_text));
        ++index;
    }

    for(int i = 0; i < ui->checker_box->value(); ++i)
    {
        vec3 diffuse_color((float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX);
        vec3 diffuse_color2((float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX,
                           (float)rand()/(float)RAND_MAX);
        texture *texture_1 = new constant_texture(diffuse_color);
        texture *texture_2 = new constant_texture(diffuse_color2);

        texture *color = new checker_texture(texture_1,texture_2);


        vec3 location((((float)rand()/(float)RAND_MAX)-.5)*10,
                      (((float)rand()/(float)RAND_MAX)-.5)*0.25,
                      (((float)rand()/(float)RAND_MAX)-.5)*10);
        list[index] = new sphere(location,0.5, new lambertian(color));
        ++index;
    }

    if(index != num_items)
    {
        std::cout << "MISCOUNT OCCURED IN RANDOM SCENE" << std::endl;
    }

    bvh_node *new_world = new bvh_node(list,num_items,0,1);

    return new_world;
}

random_scene::~random_scene()
{
    delete ui;
}
