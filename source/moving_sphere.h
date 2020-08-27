#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "surface.h"

class moving_sphere : public surface
{
public:
    moving_sphere();

    moving_sphere(vec3 cen0, vec3 cen1,float r, float t0, float t1, material* m);

    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual int bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    bool bounding_box(float t0, float t1, aabb &box) const;

    vec3 center(float time) const;

    vec3 center0, center1;
    float time0, time1;
    float radius;
    material* mat;

};

#endif // MOVING_SPHERE_H
