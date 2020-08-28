#ifndef BOX_H
#define BOX_H

#include "surface.h"
#include "surface_list.h"

class box : public surface
{
public:
    box();
    box(const vec3& p0,const vec3& p1,material *ptr);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual int bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    vec3 pmin, pmax;
    surface_list *list_ptr;
};

#endif // BOX_H
