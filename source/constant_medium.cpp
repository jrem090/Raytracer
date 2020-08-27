#include "constant_medium.h"

#include "float.h" // for MAXFLOAT definition
#include "isotropic.h"
#include "utilities.h"

constant_medium::constant_medium(surface *boundary,
                                 float density,
                                 texture *albedo)
{
    this->boundary = boundary;
    this->density  = density;
    this->phase_function = new isotropic(albedo);
}

bool constant_medium::hit(const ray &r, float t_min,
                     float t_max, hit_record &rec) const
{
    bool db = (unit_random() < 0.00001); //debug
    db = false;

    hit_record rec1, rec2;

    if(boundary->hit(r, -FLT_MAX, FLT_MAX, rec1))
    {
        if(boundary->hit(r, rec1.t+.0001,FLT_MAX,rec2))
        {
            if(db)
                std::cerr << "\nt0 t1 " << rec1.t << "  " << rec2.t << "\n";
            if(rec1.t < t_min)
                rec1.t = t_min;
            if(rec2.t > t_max)
                rec2.t = t_max;
            if(rec1.t >= rec2.t)
                return false;
            if(rec1.t < 0)
                rec1.t = 0;

            float distance_inside = (rec2.t - rec1.t)*r.direction().length();
            float hit_distance    =  -(1.0/density)*log(unit_random());

            if(hit_distance < distance_inside)
            {
                rec.t = rec1.t + hit_distance / r.direction().length();
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = vec3(1,0,0); //arbitrary
                rec.mat_ptr = phase_function;
                //db = true;
                if(db)
                {
                    std::cerr << "hit_distance: " << hit_distance <<std::endl;
                    std::cerr << "rec.t: " << rec.t <<std::endl;
                    std::cerr << "rec.p: " << rec.p <<std::endl;
                }
            }
        }
    }
    return false;
}


int constant_medium::bvh_hit(const ray &r, float t_min,
                     float t_max, hit_record &rec) const
{
    return boundary->bvh_hit(r,t_min, t_max,rec)    ;
}

bool constant_medium::bounding_box(float t0, float t1, aabb &box) const
{
    return boundary->bounding_box(t0,t1,box);
}
