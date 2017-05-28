//inline float ffmin(float a, float b) {return a < b ? a : b;}
//inline float ffmax(float a, float b) {return a > b ? a : b;}

#ifndef AABB_H
#define AABB_H

#include "ray.h"

class aabb
{
public:
    aabb();

    aabb(const vec3& a, const vec3& b);

    vec3 min() const;

    vec3 max() const;

    bool hit(const ray& r, float tmin, float tmax) const;

    aabb surrounding_box(aabb box0, aabb box1);

//private:
    vec3 _min;
    vec3 _max;
};

inline vec3 aabb::min() const
{
    return _min;
}
inline vec3 aabb::max() const
{
    return _max;
}

#endif // AABB_H
