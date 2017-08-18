#include "sphere.h"


sphere::sphere()
{

}

sphere::sphere(vec3 cen, float r, material *m) :
    center(cen),
    radius(r),
    mat(m)
{

}


bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(),r.direction());
    float b = 2*dot(oc, r.direction());
    float c = dot(oc,oc) - (radius *  radius);
    float discriminant = b*b - 4*a*c;

    //if discriminant is greater than 0 the ray hits the target
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant))/(2*a);
        if(temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center) / radius;
            rec.mat_ptr = mat;
            return true;
        }

        temp = (-b + sqrt(discriminant))/(2*a);
        if(temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }
    return false;

}

bool sphere::bounding_box(float t0, float t1, aabb &box) const
{
    box = aabb(center - vec3(radius,radius,radius),
               center + vec3(radius,radius,radius));
    return true;
}
