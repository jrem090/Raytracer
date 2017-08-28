#include "scene_widget.h"
#include "ui_scene_widget.h"

scene_widget::scene_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::scene_widget)
{
    ui->setupUi(this);
}

scene_widget::~scene_widget()
{
    delete ui;
}
