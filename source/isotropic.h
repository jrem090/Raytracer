#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "material.h"
#include "texture.h"


class isotropic : public material
{
  public:
    isotropic(texture *a) : albedo(a){}
    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        const vec3 temp(random_in_unit_sphere());
        scattered = ray(rec.p, temp,0.0);
        attenuation = albedo->value(rec.u,rec.v,rec.p);
        return true;
    }

    texture *albedo;
};

#endif // ISOTROPIC_H
