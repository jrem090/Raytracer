#ifndef SCENE_WIDGET_H
#define SCENE_WIDGET_H

#include <QWidget>
#include "../source/bvh_node.h"

namespace Ui {
class scene_widget;
}


class scene_widget : public QWidget
{
    Q_OBJECT

public:
    explicit scene_widget(QWidget *parent = 0);
    virtual bvh_node* get_scene_data() = 0;
    ~scene_widget();

private:
    Ui::scene_widget *ui;
};

#endif // SCENE_WIDGET_H
