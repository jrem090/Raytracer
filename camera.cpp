#include "camera.h"
#include "utilities.h"

camera::camera(vec3 camera_center, vec3 look_at_point, vec3 vup,
       float vfov, float aspect, float aperature,
               float focus_dist, float t0, float t1)
{
    time0 = t0;
    time1 = t1;
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

    horizontal = 2 * half_width  * focus_dist * u;
    vertical   = 2 * half_height * focus_dist * v;
    //origin = vec3(0,0,0);
}

ray camera::get_ray(float s, float t)
{
    vec3 rd     = lens_radius * random_in_unit_disk();
    vec3 offset = u* rd.x() + v * rd.y();
    float time  = time0 + unit_random()*(time1 - time0);
    return ray(origin + offset,
               lower_left_corner + s*horizontal+t*vertical-origin-offset,time);
}
