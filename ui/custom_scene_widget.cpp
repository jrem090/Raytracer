#include "custom_scene_widget.h"
#include "ui_custom_scene_widget.h"

#include "source/bvh_node.h"
#include "source/sphere.h"
#include "source/moving_sphere.h"
//include materials
#include "source/lambertian.h"
#include "source/metal.h"
#include "source/dielectric.h"
#include "source/utilities.h"
//include textures
#include "source/texture.h"
#include "source/constant_texture.h"
#include "source/checker_texture.h"
#include "source/image_texture.h"
#include "source/noise_texture.h"
#include "scene_widget.h"


#include "custom_scene/custom_item.h"
#include "custom_scene/custom_sphere.h"

custom_scene_widget::custom_scene_widget(QWidget *parent) :
    scene_widget(parent),
    ui(new Ui::custom_scene_widget)
{
    ui->setupUi(this);

    central = new QWidget();
    controlLayout = new QVBoxLayout;
    controlLayout->setSpacing(0);
    controlLayout->setMargin(0);
    controlLayout->setContentsMargins(0,0,0,0);
    controlLayout->setAlignment(Qt::AlignTop);
    central->setLayout(controlLayout);

    ui->scrollArea->setWidget(central);
    ui->scrollArea->setWidgetResizable(true);
  //  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    connect(ui->item_button, SIGNAL(clicked(bool)),
            this, SLOT(new_item()));
}

custom_scene_widget::~custom_scene_widget()
{
    delete ui;
}

bvh_node* custom_scene_widget::get_scene_data()
{

    int num_items = 5;
    surface *list[num_items];
    int index = 0;
    for(int i = 0; i < num_items; ++i)
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

    bvh_node *new_world = new bvh_node(list,num_items,0,1);

    return new_world;

}

void custom_scene_widget::new_item()
{
    custom_item *item = new custom_item();
    std::cout << "pre error?" << std::endl;
    //central->addWidget(item);
    controlLayout->addWidget(item);
    item->show();
}
