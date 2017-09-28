#ifndef PLANE_H
#define PLANE_H

#include "surface.h"

class plane : public surface
{
public:
    plane();
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;
    virtual bool bounding_box(float t0, float t1, aabb &box) const = 0;

    material *mp;
    float x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
};

#endif // PLANE_H
