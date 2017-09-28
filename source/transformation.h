#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "surface.h"

class translate : public surface
{
public:
    translate(surface *p, const vec3& displacement) :
        ptr(p),
        offset(displacement){}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    // variables
    surface *ptr;
    vec3 offset;
};

class rotate_y : public surface
{
public: 
    rotate_y(surface *p, float angle);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;
    
    surface *ptr;
    float sin_theta;
    float cos_theta;
    bool  has_box;
    aabb  bbox;
};

class rotate_x : public surface
{
public:
    rotate_x(surface *p, float angle);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    surface *ptr;
    float sin_theta;
    float cos_theta;
    bool  has_box;
    aabb  bbox;
};

class rotate_z : public surface
{
public:
    rotate_z(surface *p, float angle);
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    virtual bool bounding_box(float t0, float t1, aabb &box) const;

    surface *ptr;
    float sin_theta;
    float cos_theta;
    bool  has_box;
    aabb  bbox;
};

#endif // TRANSFORMATION_H
