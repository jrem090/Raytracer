#include "aabb.h"

aabb::aabb()
{

}

aabb::aabb(const vec3 &a, const vec3 &b)
{
    _min = a;
    _max = b;
}

bool aabb::hit(const ray &r, float tmin, float tmax) const
{
    //for each dimension, check if ray intersects slab
    for(int i =0; i < 3; ++i)
    {
        float invD = 1.0f / r.direction()[i];

        float t0 = (min()[i] - r.origin()[i]) * invD;
        float t1 = (max()[i] - r.origin()[i]) * invD;
        if(invD < 0.0f)
                std::swap(t0,t1);

        tmin = t0 > tmin ? t0 : tmin;
        tmin = t1 < tmax ? t1 : tmax;
        //older implementation. kept for academic purposes
        /*float t0 = ffmin((_min[i] - r.origin()[i]) / r.direction()[i],
                (_max[i]) - r.origin()[i] / r.direction()[i]);
        float t1 = ffmax((_min[i] - r.origin()[i]) / r.direction()[i],
                (_max[i]) - r.origin()[i] / r.direction()[i]);

        tmin = ffmax(t0, tmin);
        tmax = ffmin(t1,tmax); */

        // ray does not intersct slab
        if(tmax <= tmin)
        {
            return false;
        }

    }
    return true;
}

aabb aabb::surrounding_box(aabb box0, aabb box1)
{
    vec3 small = vec3(fmin(box0.min().x(), box1.min().x()),
                  fmin(box0.min().y(), box1.min().y()),
                  fmin(box0.min().z(), box1.min().z()));
    vec3 big   = vec3(fmax(box0.max().x(), box1.max().x()),
                  fmax(box0.max().y(), box1.max().y()),
                  fmax(box0.max().z(), box1.max().z()));

   return aabb(small,big);
}

