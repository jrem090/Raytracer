#include "transformation.h"
#include <limits>
#include <float.h>

bool translate::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    ray moved_r(r.origin()-offset, r.direction(),r.time());
    if(ptr->hit(moved_r,t_min, t_max, rec))
    {
        rec.p += offset;
        return true;
    }
    else
        return false;
}

int translate::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    ray moved_r(r.origin()-offset, r.direction(),r.time());
    return ptr->bvh_hit(moved_r,t_min, t_max, rec);
}

bool translate::bounding_box(float t0, float t1, aabb &box) const
{
    if(ptr->bounding_box(t0,t1,box))
    {
        box = aabb(box.min()+offset,box.max()+offset);
        return true;
    }
    else
        return false;
}

/////////////////////////////////////////////////////////////////////////
///             ROTATE X
/////////////////////////////////////////////////////////////////////////
rotate_x::rotate_x(surface *p, float angle)
{
    ptr = p;

    //convert degrees to radians
    float radians = (M_PI/180.0) * angle;

    //store calculated thetas for faster computing
    sin_theta = sin(radians);
    cos_theta = cos(radians);

    has_box = ptr->bounding_box(0,1,bbox);
    float flt_max = FLT_MAX;
    vec3 min(flt_max,flt_max,flt_max);
    vec3 max(-flt_max,-flt_max,-flt_max);

    for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    float x = i*bbox.max().x() + (1-i)*bbox.min().x();
                    float y = j*bbox.max().y() + (1-j)*bbox.min().y();
                    float z = k*bbox.max().z() + (1-k)*bbox.min().z();
                    float newy = cos_theta*y + sin_theta*z;
                    float newz = -sin_theta*y + cos_theta*z;
                    vec3 tester(x, newy, newz);
                    for ( int c = 0; c < 3; c++ )
                    {
                        if ( tester[c] > max[c] )
                            max[c] = tester[c];
                        if ( tester[c] < min[c] )
                            min[c] = tester[c];
                    }
                }
            }
        }
        bbox = aabb(min, max);
}

bool rotate_x::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[1] = cos_theta * r.origin()[1] - sin_theta*r.origin()[2];
    origin[2] = sin_theta * r.origin()[1] + cos_theta*r.origin()[2];

    direction[1] = cos_theta * r.direction()[1] - sin_theta*r.direction()[2];
    direction[2] = sin_theta * r.direction()[1] + cos_theta*r.direction()[2];

    ray rotated_ray(origin,direction,r.time());

    if(ptr->hit(rotated_ray,t_min,t_max,rec))
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;

        p[1] = cos_theta * rec.p[1] - sin_theta*rec.p[2];
        p[2] = sin_theta * rec.p[1] + cos_theta*rec.p[2];

        normal[1] = cos_theta * rec.normal[1] - sin_theta*rec.normal[2];
        normal[2] = sin_theta * rec.normal[1] + cos_theta*rec.normal[2];

        rec.p = p;
        rec.normal = normal;
        return true;

    }
    else
    {
        return false;
    }


}

int rotate_x::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[1] = cos_theta * r.origin()[1] - sin_theta*r.origin()[2];
    origin[2] = sin_theta * r.origin()[1] + cos_theta*r.origin()[2];

    direction[1] = cos_theta * r.direction()[1] - sin_theta*r.direction()[2];
    direction[2] = sin_theta * r.direction()[1] + cos_theta*r.direction()[2];

    ray rotated_ray(origin,direction,r.time());

    if(ptr->bvh_hit(rotated_ray,t_min,t_max,rec) > 0)
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;

        p[1] = cos_theta * rec.p[1] - sin_theta*rec.p[2];
        p[2] = sin_theta * rec.p[1] + cos_theta*rec.p[2];

        normal[1] = cos_theta * rec.normal[1] - sin_theta*rec.normal[2];
        normal[2] = sin_theta * rec.normal[1] + cos_theta*rec.normal[2];

        rec.p = p;
        rec.normal = normal;
        return 1;

    }
    else
    {
        return 0;
    }


}

bool rotate_x::bounding_box(float t0, float t1, aabb &box) const
{
    box = bbox;
    return has_box;
}

/////////////////////////////////////////////////////////////////////////
///             ROTATE Y
/////////////////////////////////////////////////////////////////////////
rotate_y::rotate_y(surface *p, float angle)
{    
    ptr = p;

    //convert degrees to radians
    float radians = (M_PI/180.0) * angle;
    
    //store calculated thetas for faster computing
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    
    has_box = ptr->bounding_box(0,1,bbox);
    float flt_max = FLT_MAX;
    vec3 min(flt_max,flt_max,flt_max);
    vec3 max(-flt_max,-flt_max,-flt_max);
    
    for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    float x = i*bbox.max().x() + (1-i)*bbox.min().x();
                    float y = j*bbox.max().y() + (1-j)*bbox.min().y();
                    float z = k*bbox.max().z() + (1-k)*bbox.min().z();
                    float newx = cos_theta*x + sin_theta*z;
                    float newz = -sin_theta*x + cos_theta*z;
                    vec3 tester(newx, y, newz);
                    for ( int c = 0; c < 3; c++ )
                    {
                        if ( tester[c] > max[c] )
                            max[c] = tester[c];
                        if ( tester[c] < min[c] )
                            min[c] = tester[c];
                    }
                }
            }
        }
        bbox = aabb(min, max);
}

bool rotate_y::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta*r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta*r.direction()[2];

    ray rotated_ray(origin,direction,r.time());

    if(ptr->hit(rotated_ray,t_min,t_max,rec))
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;

        p[0] = cos_theta * rec.p[0] - sin_theta*rec.p[2];
        p[2] = sin_theta * rec.p[0] + cos_theta*rec.p[2];

        normal[0] = cos_theta * rec.normal[0] - sin_theta*rec.normal[2];
        normal[2] = sin_theta * rec.normal[0] + cos_theta*rec.normal[2];

        rec.p = p;
        rec.normal = normal;
        return true;

    }
    else
    {
        return false;
    }


}

int rotate_y::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta * r.origin()[0] + cos_theta*r.origin()[2];

    direction[0] = cos_theta * r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta * r.direction()[0] + cos_theta*r.direction()[2];

    ray rotated_ray(origin,direction,r.time());

    if(ptr->bvh_hit(rotated_ray,t_min,t_max,rec) > 0)
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;

        p[0] = cos_theta * rec.p[0] - sin_theta*rec.p[2];
        p[2] = sin_theta * rec.p[0] + cos_theta*rec.p[2];

        normal[0] = cos_theta * rec.normal[0] - sin_theta*rec.normal[2];
        normal[2] = sin_theta * rec.normal[0] + cos_theta*rec.normal[2];

        rec.p = p;
        rec.normal = normal;
        return 1;

    }
    else
    {
        return 0;
    }


}

bool rotate_y::bounding_box(float t0, float t1, aabb &box) const
{
    box = bbox;
    return has_box;
}

/////////////////////////////////////////////////////////////////////////
///             ROTATE Z
/////////////////////////////////////////////////////////////////////////
rotate_z::rotate_z(surface *p, float angle)
{
    ptr = p;

    //convert degrees to radians
    float radians = (M_PI/180.0) * angle;

    //store calculated thetas for faster computing
    sin_theta = sin(radians);
    cos_theta = cos(radians);

    has_box = ptr->bounding_box(0,1,bbox);
    float flt_max = FLT_MAX;
    vec3 min(flt_max,flt_max,flt_max);
    vec3 max(-flt_max,-flt_max,-flt_max);

    for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    float x = i*bbox.max().x() + (1-i)*bbox.min().x();
                    float y = j*bbox.max().y() + (1-j)*bbox.min().y();
                    float z = k*bbox.max().z() + (1-k)*bbox.min().z();
                    float newx = cos_theta*x + sin_theta*y;
                    float newy = -sin_theta*x + cos_theta*y;
                    vec3 tester(newx, newy, z);
                    for ( int c = 0; c < 3; c++ )
                    {
                        if ( tester[c] > max[c] )
                            max[c] = tester[c];
                        if ( tester[c] < min[c] )
                            min[c] = tester[c];
                    }
                }
            }
        }
        bbox = aabb(min, max);
}

bool rotate_z::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta*r.origin()[1];
    origin[1] = sin_theta * r.origin()[0] + cos_theta*r.origin()[1];

    direction[0] = cos_theta * r.direction()[0] - sin_theta*r.direction()[1];
    direction[1] = sin_theta * r.direction()[0] + cos_theta*r.direction()[1];

    ray rotated_ray(origin,direction,r.time());

    if(ptr->hit(rotated_ray,t_min,t_max,rec))
    {
        vec3 p = rec.p;
        vec3 normal = rec.normal;

        p[0] = cos_theta * rec.p[0] - sin_theta*rec.p[1];
        p[1] = sin_theta * rec.p[0] + cos_theta*rec.p[1];

        normal[0] = cos_theta * rec.normal[0] - sin_theta*rec.normal[1];
        normal[1] = sin_theta * rec.normal[0] + cos_theta*rec.normal[1];

        rec.p = p;
        rec.normal = normal;
        return true;

    }
    else
    {
        return false;
    }


}

int rotate_z::bvh_hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 origin = r.origin();
    vec3 direction = r.direction();

    origin[0] = cos_theta * r.origin()[0] - sin_theta*r.origin()[1];
    origin[1] = sin_theta * r.origin()[0] + cos_theta*r.origin()[1];

    direction[0] = cos_theta * r.direction()[0] - sin_theta*r.direction()[1];
    direction[1] = sin_theta * r.direction()[0] + cos_theta*r.direction()[1];

    ray rotated_ray(origin,direction,r.time());

    return ptr->hit(rotated_ray,t_min,t_max,rec);
}


bool rotate_z::bounding_box(float t0, float t1, aabb &box) const
{
    box = bbox;
    return has_box;
}


