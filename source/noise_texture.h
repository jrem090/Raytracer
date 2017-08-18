#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "texture.h"

class noise_texture : public texture
{
public:
    noise_texture(){scale = 1.0;}
    noise_texture(float sc) : scale(sc){}
    virtual vec3 value(float u, float v, const vec3 &p) const
    {
        return vec3(1,1,1) * noise(scale*p);
    }

private:
    float scale;
};

#endif // NOISE_TEXTURE_H
