#include "custom_scene_widget.h"
#include "ui_custom_scene_widget.h"

CustomSceneWidget::CustomSceneWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomSceneWidget)
{
    ui->setupUi(this);
}

CustomSceneWidget::~CustomSceneWidget()
{
    delete ui;
}
