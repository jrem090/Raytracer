#include "xy_rect.h"

xy_rect::xy_rect()
{

}

xy_rect::xy_rect(float x0, float x1, float y0, float y1, float k, material *mat)
{
    this->x0 = x0;
    this->x1 = x1;
    this->y0 = y0;
    this->y1 = y1;
    this->k  = k;
    this->mp = mat;
}

bool xy_rect::bounding_box(float t0, float t1, aabb &box) const
{
    box = aabb(vec3(x0,y0, k - .000001), vec3(x1,y1, k+.000001));
    return true;
}

bool xy_rect::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = (k-r.origin().z()) / r.direction().z();

    //if t is not within bounds return false
    if(t < t_min || t > t_max)
        return false;

    float x = r.origin().x() + t*r.direction().x();
    float y = r.origin().y() + t*r.direction().y();

    // if ray is not in between x and y return false
    if(x < x0 || x > x1 || y < y0 || y > y1)
        return false;

    rec.u = (x-x0)/(x1-x0);
    rec.v = (y-y0)/(y1-y0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0,0,1);
    return true;
}

