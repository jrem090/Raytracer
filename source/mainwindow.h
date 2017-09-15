#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vec3.h"
#include "bvh_node.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void raytrace();


private:
    Ui::MainWindow *ui;

    vec3  look_at;
    vec3  look_from;

    unsigned int num_diffuse;
    unsigned int num_glass;
    unsigned int num_metal;

    bvh_node* world;

    bvh_node* build_checker_scene(unsigned int num_diffuse,
                                 unsigned int num_glass,
                                 unsigned int num_metal);

    bvh_node* build_cornell_box();

};

#endif // MAINWINDOW_H
