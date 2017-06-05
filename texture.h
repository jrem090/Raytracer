#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec3.h"
#include "utilities.h"

class texture
{
public:
    virtual vec3 value(float u, float v, const vec3& p) const = 0;
};


#endif // TEXTURE_H
