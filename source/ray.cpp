#include "ray.h"

ray::ray()
{

}

ray::ray(const vec3 &a, const vec3 &b, float ti = 0.0)
{
    A = a;
    B = b;
    ray_time = ti;
}


//vec3 ray::origin() const
//{
//    return A;
//}

//vec3 ray::direction() const
//{
//    return B;
//}

//vec3 ray::point_at_parameter(float t) const
//{
//    return A + t*B;
//}

