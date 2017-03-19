#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void updateBlue(int new_blue);

private:
    Ui::MainWindow *ui;
    float blue;
};

#endif // MAINWINDOW_H
