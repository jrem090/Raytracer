#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "utilities.h"


/**
 * @brief The dielectric class
 * This class describes a material that reflects light/rays.
 */
class metal : public material
{
public:

    /**
     * @brief metal
     * @param a vec3 defining albedo
     * @param f float describing fuzziness [0,1]
     */
    metal(const vec3& a, float f = 0) : albedo(a)
    {
        //sanitize inputs
        if(f>1)
        {
            fuzz = 1;
        }
        else if(f<0)
        {
            fuzz = 0;
        }
        else
            fuzz = f;
    }


    /**
     * @brief scatter
     * @param r_in stored ray
     * @param rec stored hit record
     * @param attenuation stored light
     * @param scattered stored ray
     * @return
     */
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {

        vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere(), r_in.time());
        attenuation = albedo;
        return (dot(scattered.direction(),rec.normal) > 0);
    }
    vec3 albedo;
    float fuzz;
};

#endif // METAL_H
