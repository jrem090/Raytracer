#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"


/**
 * @brief The camera class
 * This class defines a camera object. The camera object is responsible for
 * sending out rays to determine pixel colors
 */
class camera
{
public :
    /**
     * @brief camera constructor
     * @param camera_center vec3 (x,y,z) coordinates of camera in 3d space
     * @param look_at_point vec3 (x,y,z) coordinates where camera is facing
     * @param vup   vec3 describes the up camera direction
     * @param vfov   float vertical field of vision
     * @param aspect float aspect ratio (width / height)
     * @param aperature  float amount of light let into camera
     * @param focus_dist float distance to focus image around
     */
    camera(vec3 camera_center,vec3 look_at_point, vec3 vup,
           float vfov, float aspect, float aperature, float focus_dist);

    /**
     * @brief get_ray
     * returns a ray emitted from a specified pixel location plus
     * some random offset based on aperature and focus
     * @param s pixel's x location
     * @param t pixel's x location
     * @return return ray for the given (s,t) pixel modified by an offset
     */
    ray get_ray(float s, float t);

    vec3 origin;
    vec3 vertical;
    vec3 horizontal;
    vec3 lower_left_corner;
    vec3 u, v, w;
    float lens_radius;

};


#endif // CAMERA_H
