//inline float ffmin(float a, float b) {return a < b ? a : b;}
//inline float ffmax(float a, float b) {return a > b ? a : b;}

#ifndef AABB_H
#define AABB_H

#include "ray.h"

/**
 * @brief The aabb class defines an Axis-Aligned Bounding box
 * This class defines a box in an x,y,z coordinate frame that bounds a surface
 * or group of surfaces.
 */
class aabb
{
public:
    aabb();

    /**
     * @brief aabb
     * @param a vec3 representing one corner of surface/bounds
     * @param b vec3 representing opposite corner of surface/bounds
     */
    aabb(const vec3& a, const vec3& b);

    /**
     * @brief min
     * @return return minimum (x,y,z) coordinates
     */
    vec3 min() const;

    /**
     * @brief max
     * @return return maximum (x,y,z) coordinates
     */
    vec3 max() const;

    /**
     * @brief hit check if a ray r hits/interacts with the bounding box
     * @param r ray
     * @param tmin closest distance
     * @param tmax max distance
     * @return
     */
    bool hit(const ray& r, float tmin, float tmax) const;

    /**
     * @brief surrounding_box returns an AABB containing both specified AABBs
     * @param box0 first aabb to be merged
     * @param box1 second aabb to be merged
     * @return
     */
    aabb surrounding_box(aabb box0, aabb box1);

//private:
    vec3 _min;
    vec3 _max;
};

inline vec3 aabb::min() const
{
    return _min;
}
inline vec3 aabb::max() const
{
    return _max;
}

#endif // AABB_H
