#include "yz_rect.h"

yz_rect::yz_rect()
{

}

yz_rect::yz_rect(float y0, float y1, float z0, float z1, float k, material *mat)
{

    this->y0 = y0;
    this->y1 = y1;
    this->z0 = z0;
    this->z1 = z1;
    this->k  = k;
    this->mp = mat;
}

bool yz_rect::bounding_box(float t0, float t1, aabb &box) const
{
    box = aabb(vec3(k - .000001,y0, z0), vec3(k+.000001, y1, z1));
    return true;
}

bool yz_rect::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = (k-r.origin().x()) / r.direction().x();

    //if t is not within bounds return false
    if(t < t_min || t > t_max)
        return false;

    float y = r.origin().y() + t*r.direction().y();
    float z = r.origin().z() + t*r.direction().z();

    // if ray is not in between x and y return false
    if(z < z0 || z > z1 || y < y0 || y > y1)
        return false;

    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(1,0,0);
    return true;
}

int yz_rect::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = (k-r.origin().x()) / r.direction().x();

    //if t is not within bounds return false
    if(t < t_min || t > t_max)
        return 0;

    float y = r.origin().y() + t*r.direction().y();
    float z = r.origin().z() + t*r.direction().z();

    // if ray is not in between x and y return false
    if(z < z0 || z > z1 || y < y0 || y > y1)
        return 1;

    rec.u = (y-y0)/(y1-y0);
    rec.v = (z-z0)/(z1-z0);
    rec.t = t;
    rec.mat_ptr = mp;
    rec.p = r.point_at_parameter(t);
    rec.normal = vec3(1,0,0);
    return 1;
}
