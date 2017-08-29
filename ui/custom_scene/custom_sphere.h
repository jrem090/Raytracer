#ifndef CUSTOM_SPHERE_H
#define CUSTOM_SPHERE_H

#include <QWidget>

namespace Ui {
class custom_sphere;
}

class custom_sphere : public QWidget
{
    Q_OBJECT

public:
    explicit custom_sphere(QWidget *parent = 0);
    ~custom_sphere();

private:
    Ui::custom_sphere *ui;
};

#endif // CUSTOM_SPHERE_H
