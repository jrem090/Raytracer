#include "moving_sphere.h"

moving_sphere::moving_sphere()
{

}

moving_sphere::moving_sphere(vec3 cen0, vec3 cen1,float r,
                             float t0, float t1, material* m) :
    center0(cen0),
    center1(cen1),
    radius(r),
    time0(t0),
    time1(t1),
    mat(m)
{

}

vec3 moving_sphere::center(float time) const
{
    return center0 + ((time - time0) / (time1 -time0)) * (center1 - center0);
}
bool moving_sphere::hit(const ray &r,
                        float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin()-center(r.time());
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
            rec.normal = (rec.p-center(r.time())) / radius;
            rec.mat_ptr = mat;
            return true;
        }

        temp = (-b + sqrt(discriminant))/(2*a);
        if(temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center(r.time())) / radius;
            rec.mat_ptr = mat;
            return true;
        }
    }
    return false;
}

int moving_sphere::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin()-center(r.time());
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
            rec.normal = (rec.p-center(r.time())) / radius;
            rec.mat_ptr = mat;
            return 1;
        }

        temp = (-b + sqrt(discriminant))/(2*a);
        if(temp > t_min && temp < t_max)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p-center(r.time())) / radius;
            rec.mat_ptr = mat;
            return 1;
        }
    }
    return 0;
}

bool moving_sphere::bounding_box(float t0, float t1, aabb &box) const
{

    aabb box0 = aabb(center0 - vec3(radius,radius,radius),
               center0 + vec3(radius,radius,radius));
    aabb box1 = aabb(center1 - vec3(radius,radius,radius),
               center1 + vec3(radius,radius,radius));

    vec3 small = vec3(fmin(box0.min().x(), box1.min().x()),
                  fmin(box0.min().y(), box1.min().y()),
                  fmin(box0.min().z(), box1.min().z()));

    vec3 big   = vec3(fmax(box0.max().x(), box1.max().x()),
                  fmax(box0.max().y(), box1.max().y()),
                  fmax(box0.max().z(), box1.max().z()));

    box = aabb(small,big);
    return true;
}
