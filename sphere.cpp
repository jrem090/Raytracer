#include "sphere.h"


sphere::sphere()
{

}

sphere::sphere(vec3 cen, float r) :
    center(cen),
    radius(r)
{

}

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(),r.direction());
    float b = 2*dot(oc, r.direction());
    float c = dot(oc,oc) - (radius *  radius);
    float discriminant = b*b - 4*a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant))/(2*a);
        if(temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center) / radius;
            return true;
        }

        temp = (-b + sqrt(discriminant))/(2*a);
        if(temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center) / radius;
            return true;
        }
    }
    else
    {
        return false;
    }
}
