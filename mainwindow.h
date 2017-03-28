#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "vec3.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
//     vec3 random_in_unit_sphere();
    ~MainWindow();

public slots:
    void raytrace();
    void updateBlue(int new_blue);

private:
    Ui::MainWindow *ui;
    float blue;
};

#endif // MAINWINDOW_H
