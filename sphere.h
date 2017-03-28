#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"

class material;

class sphere : public surface
{
public:
    sphere();
    sphere(vec3 cen, float r, material* m);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    material* mat;
    vec3 center;
    float radius;
};

#endif // SPHERE_H
