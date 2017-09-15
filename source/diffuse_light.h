#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "material.h"
#include "texture.h"


class diffuse_light : public material
{
public:
    diffuse_light(texture *a) : emit_texture(a){}
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const
    { return false;}

    virtual vec3 emitted(float u, float v, const vec3& p) const
    {
        return emit_texture->value(u,v,p);
    }

    texture *emit_texture;
};

#endif // DIFFUSE_LIGHT_H
