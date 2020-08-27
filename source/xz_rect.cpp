#include "xz_rect.h"

xz_rect::xz_rect()
{

}

xz_rect::xz_rect(float x0, float x1, float z0, float z1, float k, material *mat)
{
    this->x0 = x0;
    this->x1 = x1;
    this->z0 = z0;
    this->z1 = z1;
    this->k  = k;
    this->mp = mat;
}

bool xz_rect::bounding_box(float t0, float t1, aabb &box) const
{
    box = aabb(vec3(x0, k - .000001,z0), vec3(x1, k+.000001, z1));
    return true;
}

bool xz_rect::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = (k-r.origin().y()) / r.direction().y();

    //if t is not within bounds return false
    if(t < t_min || t > t_max)
        return false;

    float x = r.origin().x() + t*r.direction().x();
    float z = r.origin().z() + t*r.direction().z();

    // if ray is not in between x and y return false
    if(x < x0 || x > x1 || z < z0 || z > z1)
        return false;

    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0,1,0);
    return true;
}

int xz_rect::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = (k-r.origin().y()) / r.direction().y();

    //if t is not within bounds return false
    if(t < t_min || t > t_max)
        return 0;

    float x = r.origin().x() + t*r.direction().x();
    float z = r.origin().z() + t*r.direction().z();

    // if ray is not in between x and y return false
    if(x < x0 || x > x1 || z < z0 || z > z1)
        return 0;

    rec.u = (x-x0)/(x1-x0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(0,1,0);
    return 1;
}
