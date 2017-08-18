#ifndef MATERIAL_H
#define MATERIAL_H

#include "surface.h"

/**
 * @brief The material class
 * abstract class defining a base material. The children of this class are
 * used to define the behavior for when a ray hits an object/mesh that is covered
 * by the material
 */
class material
{
public:

    /**
     * @brief scatter
     * @param r_in stored ray
     * @param rec stored hit record
     * @param attenuation stored light
     * @param scattered stored ray
     * @return
     */
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const = 0;
};


#endif // MATERIAL_H
