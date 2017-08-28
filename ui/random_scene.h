#ifndef RANDOM_SCENE_H
#define RANDOM_SCENE_H

#include "scene_widget.h"
#include <QWidget>

namespace Ui {
class random_scene;
}

class random_scene : public scene_widget
{
    Q_OBJECT

public:
    explicit random_scene(QWidget *parent = 0);
    virtual bvh_node* get_scene_data();
    ~random_scene();

private:
    Ui::random_scene *ui;
    bvh_node* world;
};

#endif // RANDOM_SCENE_H
