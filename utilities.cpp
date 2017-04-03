#include "utilities.h"


float unit_random()
{
    return (float)rand() * 1.0/(float)RAND_MAX;
}

vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.0*vec3(unit_random(),unit_random(),0);
        p = p - vec3(1,1,0);
    } while(dot(p,p) >= 1.0);
    return p;
}

vec3 random_in_unit_sphere()
{
    vec3 p;
    //generate point in unit cube. if point is inside unit sphere return
    //otherwise repeat.
    do{
        p = 2.0*vec3(unit_random(),unit_random(),unit_random());
        p = p - vec3(1,1,1);
    }while (p.squared_length() >= 1.0);
    return p;
}


vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v,n)*n;
}


bool refract(const vec3& v,
             const vec3& n,
             float ni_over_nt,
             vec3& refracted)
{
    vec3 uv  = unit_vector(v);
    float dt = dot(uv, n);

    float discriminant = 1.0 - ni_over_nt * ni_over_nt
            * (1-dt*dt);
    if(discriminant > 0)
    {
        refracted = ni_over_nt*(uv - n*dt) -
                n * sqrt(discriminant);
        return true;
    }
    else
        return false;
}

