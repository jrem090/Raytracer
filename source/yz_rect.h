#ifndef YZ_RECT_H
#define YZ_RECT_H

#include "surface.h"

class yz_rect : public surface
{
public:
    yz_rect();

    yz_rect(float y0, float y1, float z0,float z1,float k, material* mat);

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual int bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;


    material *mp;
    float y0, y1, z0, z1, k;


};

#endif // YZ_RECT_H
