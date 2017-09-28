#ifndef XY_RECT_H
#define XY_RECT_H

#include "surface.h"
//#include "material.h"

class xy_rect : public surface
{
public:
    xy_rect();

    xy_rect(float x0, float x1, float y0,float y1,float k, material* mat);

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    virtual bool bounding_box(float t0, float t1, aabb &box) const;


    material *mp;
    float x0, x1, y0, y1, k;

};

#endif // XY_RECT_H
