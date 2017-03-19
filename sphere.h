#ifndef SPHERE_H
#define SPHERE_H
#include "surface.h"


class sphere : public surface
{
public:
    sphere();
    sphere(vec3 cen, float r);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    vec3 center;
    float radius;
};

#endif // SPHERE_H
