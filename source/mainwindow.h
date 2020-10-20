#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "raytracer.h"

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
    void finish_raytrace();
    void update_progress(float percent);
    void scene_change(int scene);
    void show_help();
    void show_bvh();

signals:
void    raytrace_command(int width, int height, bvh_node* world,
                     int samples,
                     float cam_x, float cam_y, float cam_z,
                     float focal_x, float focal_y, float focal_z);


private:
    Ui::MainWindow *ui;

    vec3  look_at;
    vec3  look_from;

    Raytracer *raytracer;
    QThread raytrace_thread;

    bvh_node* world;

    bvh_node* build_checker_scene(unsigned int num_diffuse,
                                 unsigned int num_glass,
                                 unsigned int num_metal);

    bvh_node* build_cornell_box();

};

#endif // MAINWINDOW_H
