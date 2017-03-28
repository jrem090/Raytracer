#include "surface_list.h"

surface_list::surface_list()
{

}

surface_list::surface_list(surface **s, int n) :
    list(s),
    list_size(n)
{

}

bool surface_list::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for(int i = 0; i < list_size; i++)
    {
        if(list[i]->hit(r, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
