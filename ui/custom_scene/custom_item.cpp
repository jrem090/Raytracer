#include "custom_item.h"
#include "ui_custom_item.h"

custom_item::custom_item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::custom_item)
{
    ui->setupUi(this);
}

custom_item::~custom_item()
{
    delete ui;
}
