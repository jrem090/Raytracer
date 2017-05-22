#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "utilities.h"

/**
 * @brief The lambertian class
 * his class describes a material with a diffuse shader
 */
class lambertian : public material
{
public:
    /**
     * @brief lambertian
     * @param a alebedo
     */
    lambertian(const vec3& a) : albedo(a){}


    /**
     * @brief scatter
     * @param r_in stored ray
     * @param rec stored hit record
     * @param attenuation stored light
     * @param scattered stored ray
     * @return
     */
    virtual bool scatter(const ray &r_in,
                         const hit_record &rec,
                         vec3 &attenuation,
                         ray &scattered) const
    {
        //define a randomly scattered ray and accumulate albedo;
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target-rec.p , r_in.time());
        attenuation = albedo;
        return true;
    }


    vec3 albedo;
};



#endif // LAMBERTIAN_H
