#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H

#include "surface.h"

class surface_list : public surface
{
public:
    surface_list();
    surface_list(surface **s, int n);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual int bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;
    surface **list;
    int list_size;
};

#endif // SURFACE_LIST_H
