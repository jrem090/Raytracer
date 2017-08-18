#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "utilities.h"


/**
 * @brief schlick Function approximating reflectivity of glass at varying angles
 * @param cosine
 * @param ref_idx
 * @return
 */
float schlick(float cosine, float ref_idx)
{
    float r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0)*pow((1-cosine),5);
}

/**
 * @brief The dielectric class
 * This class describes a material that reflects and refracts light/rays.
 * An example would be glass.
 */
class dielectric : public material
{
    public:
    /**
     * @brief dielectric constructor
     * @param a albedo
     * @param f refractive index
     */
    dielectric(const vec3& a, float f = 1.1) : albedo(a),ref_idx(f){}

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

        //define parameters
        vec3 outward_normal = rec.normal;
        vec3 reflected      = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = albedo;
        vec3 refracted;
        float reflect_prob;
        float cosine;

        //handle ray input directions(going into object, coming out of object
        if(dot(r_in.direction(), rec.normal)>0)
        {
            outward_normal = -rec.normal;
            ni_over_nt     = ref_idx;
            cosine         = ref_idx * dot(r_in.direction(), rec.normal) /
                                r_in.direction().length();
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt     = 1.0 / ref_idx;
            cosine         = -dot(r_in.direction(), rec.normal) /
                                r_in.direction().length();
        }

        // calculate probability ray is reflected
        if(refract(r_in.direction(), outward_normal, ni_over_nt,refracted))
        {
            reflect_prob = schlick(cosine, ref_idx);
        }
        else
        {
            scattered    = ray(rec.p,reflected, r_in.time());
            reflect_prob = 1.0;
        }

        //using probablility generated, reflect or refract ray
        if(unit_random() < reflect_prob)
        {
            scattered    = ray(rec.p,reflected, r_in.time());
        }
        else
        {
            scattered    = ray(rec.p,refracted, r_in.time());
        }

        return true;

    }

    float ref_idx;
    vec3 albedo;
};
#endif // DIELECTRIC_H
