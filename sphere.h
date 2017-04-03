#ifndef SPHERE_H
#define SPHERE_H

#include "surface.h"

class material;

class sphere : public surface
{
public:
    /**
     * @brief sphere constructor
     */
    sphere();

    /**
     * @brief sphere constructor
     * @param cen vec3 location of center
     * @param r float radius
     * @param m material pointer to material
     */
    sphere(vec3 cen, float r, material* m);

    /**
     * @brief hit
     * @param r ray
     * @param t_min minimum distance to hit
     * @param t_max maximum distance to hit
     * @param rec hit record
     * @return  is hit
     */
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;

    material* mat;
    vec3 center;
    float radius;
};

#endif // SPHERE_H
