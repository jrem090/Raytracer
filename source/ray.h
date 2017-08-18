#ifndef RAY_H
#define RAY_H
#include "vec3.h"

/**
 * @brief The ray class
 * This class defines a ray using a point to originat3e from and a point to travel to
 */
class ray
{
public:
    /**
     * @brief ray constructor
     */
    ray();

    /**
     * @brief ray constructor
     * @param a source
     * @param b destination
     */
    ray(const vec3& a, const vec3& b, float ti);

    /**
     * @brief origin
     * @return ray origin
     */
    vec3 origin() const;

    /**
     * @brief direction
     * @return destination/direction
     */
    vec3 direction() const;

    /**
     * @brief point_at_parameter
     * @param t time value
     * @return
     */
    vec3 point_at_parameter(float t) const;

    float time() const;

    /// origin
    vec3 A;

    ///direction
    vec3 B;

    float ray_time;
};

//Inline Functions


inline vec3 ray::origin() const
{
    return A;
}

inline vec3 ray::direction() const
{
    return B;
}

inline vec3 ray::point_at_parameter(float t) const
{
    return A + t*B;
}

inline float ray::time() const
{
    return ray_time;
}
//vec3 random_in_unit_sphere();
#endif // RAY_H
