#ifndef XZ_RECT_H
#define XZ_RECT_H

#include "surface.h"

class xz_rect : public surface
{
public:
    xz_rect();

    xz_rect(float x0, float x1, float z0,float z1,float k, material* mat);

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual int bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    material *mp;
    float x0, x1, z0, z1, k;

};

#endif // XZ_RECT_H
