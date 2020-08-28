#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QObject>

#include "vec3.h"
#include "bvh_node.h"

class Raytracer : public QObject
{
    Q_OBJECT
public:
    explicit Raytracer(QObject *parent = nullptr);

private:
    vec3 color(const ray& r, surface *world, int depth);

signals:
void raytrace_complete();
void progress_update(float percentage);

public slots:
        void raytrace(int width, int height, bvh_node* world,
                      int samples,
                      float cam_x, float cam_y, float cam_z,
                      float focal_x, float focal_y, float focal_z);

};

#endif // RAYTRACER_H
