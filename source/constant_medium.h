#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "surface.h"
#include "texture.h"

class constant_medium : public surface
{
public:
    constant_medium(surface *boundary, float density, texture *albedo);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;


    surface  *boundary;
    float     density;
    material *phase_function;
};

#endif // CONSTANT_MEDIUM_H
