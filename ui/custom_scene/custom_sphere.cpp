#include "custom_sphere.h"
#include "ui_custom_sphere.h"

custom_sphere::custom_sphere(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custom_sphere)
{
    ui->setupUi(this);
}

custom_sphere::~custom_sphere()
{
    delete ui;
}
