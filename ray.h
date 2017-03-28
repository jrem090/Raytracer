#ifndef RAY_H
#define RAY_H
#include "vec3.h"

class ray
{
public:
    ray();
    ray(const vec3& a, const vec3& b);
    vec3 origin() const;
    vec3 direction() const;
    vec3 point_at_parameter(float t) const;

    vec3 A;
    vec3 B;
};

vec3 random_in_unit_sphere();
#endif // RAY_H
