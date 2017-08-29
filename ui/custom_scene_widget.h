#ifndef CUSTOM_SCENE_WIDGET_H
#define CUSTOM_SCENE_WIDGET_H

#include "scene_widget.h"
#include <QWidget>

namespace Ui {
class custom_scene_widget;
}

class custom_scene_widget : public scene_widget
{
    Q_OBJECT

public:
    explicit custom_scene_widget(QWidget *parent = 0);
    virtual bvh_node* get_scene_data();
    ~custom_scene_widget();

    QWidget *central;
    QLayout *controlLayout;

public slots:
    void new_item();


private:
    Ui::custom_scene_widget *ui;
};

#endif // CUSTOM_SCENE_WIDGET_H
