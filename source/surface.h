#ifndef SURFACE_H
#define SURFACE_H


#include "aabb.h"

class material;

/**
 * @brief The hit_record struct
 */
struct hit_record
{
    float t; //distance
    float u;
    float v;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class surface{
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    virtual int bvh_hit(const ray& r, float t_min, float t_max,hit_record& rec) const = 0;
    virtual bool bounding_box(float t0, float t1, aabb& box) const = 0;
};

#endif // SURFACE_H
