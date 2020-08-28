#ifndef BVHVIEWER_H
#define BVHVIEWER_H

#include <QObject>

#include "vec3.h"
#include "bvh_node.h"

class BVHViewer : public QObject
{
    Q_OBJECT
public:
    explicit BVHViewer(QObject *parent = nullptr);

private:
    int counter(const ray& r, surface *world, int depth);

signals:
    void bvh_complete();
    void progress_update(float percentage);

public slots:
        void bvh_trace(int width, int height, bvh_node* world,
                      int samples,
                      float cam_x, float cam_y, float cam_z,
                      float focal_x, float focal_y, float focal_z);

};

#endif // BVHVIEWER_H
