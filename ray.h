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
    ray(const vec3& a, const vec3& b);

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

    /// origin
    vec3 A;

    ///direction
    vec3 B;
};

//vec3 random_in_unit_sphere();
#endif // RAY_H
