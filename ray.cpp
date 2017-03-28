#include "ray.h"

ray::ray()
{

}

ray::ray(const vec3 &a, const vec3 &b)
{
    A = a;
    B = b;
}

vec3 ray::origin() const
{
    return A;
}

vec3 ray::direction() const
{
    return B;
}

vec3 ray::point_at_parameter(float t) const
{
    return A + t*B;
}

vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        p = 2.0*vec3((float)rand()/(float)RAND_MAX,
                (float)rand()/(float)RAND_MAX,
                (float)rand()/(float)RAND_MAX) - vec3(1,1,1);
    }while (p.squared_length() >= 1.0);
    return p;
}
