#ifndef FLIP_NORMALS_H
#define FLIP_NORMALS_H

#include  "surface.h"

class flip_normals : public surface
{
public:
    flip_normals(surface* p):ptr(p){}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const
    {
        if(ptr->hit(r, t_min, t_max, rec))
        {
            rec.normal = -rec.normal;
            return true;
        }
        else
            return false;
    }

    virtual int bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
        if(ptr->hit(r, t_min, t_max, rec))
        {
            rec.normal = -rec.normal;
            return 1;
        }
        else
            return 0;
   }

    virtual bool bounding_box(float t0, float t1, aabb &box) const
    {
        return ptr->bounding_box(t0,t1,box);
    }

    surface *ptr;
};
#endif // FLIP_NORMALS_H
