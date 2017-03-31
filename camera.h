#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.0*vec3((float)rand()/(float)RAND_MAX,
                (float)rand()/(float)RAND_MAX,0);
        p = p - vec3(1,1,0);
    } while(dot(p,p) >= 1.0);
    return p;
}

class camera
{
public :
    camera(vec3 camera_center,vec3 look_at_point, vec3 vup,
           float vfov, float aspect, float aperature, float focus_dist)
    {
        lens_radius = aperature/2;
        float theta = vfov * M_PI/180; //convert to radians
        float half_height = tan(theta/2);
        float half_width  = aspect * half_height;

        origin = camera_center;

        w = unit_vector(origin - look_at_point);
        u = unit_vector(cross(vup,w));
        v = unit_vector(cross(w,u));

        lower_left_corner = vec3(-half_width,-half_height,-1.0);
        lower_left_corner = origin - half_width* focus_dist * u
                -half_height * focus_dist * v - focus_dist * w;

        horizontal = 2*half_width  * focus_dist * u;
        vertical   = 2*half_height * focus_dist * v;
        //origin = vec3(0,0,0);
    }

    ray get_ray(float s, float t)
    {
        vec3 rd     = lens_radius * random_in_unit_disk();
        vec3 offset = u* rd.x() + v * rd.y();
        return ray(origin + offset,
                   lower_left_corner + s*horizontal+t*vertical-origin-offset);
    }

    vec3 origin;
    vec3 vertical;
    vec3 horizontal;
    vec3 lower_left_corner;
    vec3 u, v, w;
    float lens_radius;

};


#endif // CAMERA_H
