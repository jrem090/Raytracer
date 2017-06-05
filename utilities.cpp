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

float noise(const vec3 &p)
{
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());
    u = u*u*(3-2*u);
    v = v*v*(3-2*v);
    w = w*w*(3-2*w);
    int i   = floor(p.x());
    int j   = floor(p.y());
    int k   = floor(p.z());
    float c[2][2][2];

    if(ranfloat == NULL)
    {
        ranfloat = perlin_generate();
        perm_x   = perlin_generate_perm();
        perm_y   = perlin_generate_perm();
        perm_z   = perlin_generate_perm();
    }

    for(int di=0; di<2; ++di)
        for(int dj=0; dj<2; ++dj)
            for(int dk=0; dk<2; ++dk)
                c[di][dj][dk] = ranfloat[perm_x[(i+di) & 255] ^
                        perm_y[(j+dj) & 255] ^
                        perm_z[(k+dk) & 255]];


    return trilinear_interp(c,u,v,w);

}

float * perlin_generate()
{
    float * p = new float[256];
    for(unsigned int i = 0; i < 256; ++i)
    {
        p[i] = unit_random();
    }
    return p;
}

void permute(int *p, int n)
{
    for(int i = n-1; i > 0; --i)
    {
        int target = int(unit_random()*(i+1));
        int tmp    = p[i];
        p[i]       = p[target];
        p[target]  = tmp;
    }
}

int* perlin_generate_perm()
{
    int * p = new int[256];
    for(unsigned int i = 0; i < 256; ++i)
    {
       p[i] = i;
    }
    permute(p,256);
    return p;
}

float trilinear_interp(float c[2][2][2], float u, float v, float w)
{
    float accum = 0;
    for (int i=0; i<2; ++i)
    {
        for(int j=0;j<2;++j)
        {
            for(int k=0;k<2;++k)
            {
                accum += (i*u + (1-i)*(1-u)) *
                         (j*v + (1-j)*(1-v)) *
                         (k*w + (1-k)*(1-w)) *
                         c[i][j][k];
            }
        }
    }
    return accum;
}


