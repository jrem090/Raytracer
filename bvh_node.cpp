#include "bvh_node.h"

#include "utilities.h"

//===================================================================
//compare methods used in construction of bvh_node
int box_x_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    surface *ah = *(surface**)a;
    surface *bh = *(surface**)b;
    if(!ah->bounding_box(0,0,box_left) || bh->bounding_box(0,0,box_right))
    {
        std::cerr << "no bounding box in bvh_node x_compare" << std::endl;
    }
    if(box_left.min().x() - box_right.min().x() < 0.0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int box_y_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    surface *ah = *(surface**)a;
    surface *bh = *(surface**)b;
    if(!ah->bounding_box(0,0,box_left) || !bh->bounding_box(0,0,box_right))
    {
        std::cerr << "no bounding box in bvh_node y compare" << std::endl;
    }
    if(box_left.min().y() - box_right.min().y() < 0.0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int box_z_compare (const void * a, const void * b)
{
    aabb box_left, box_right;
    surface *ah = *(surface**)a;
    surface *bh = *(surface**)b;
    if(!ah->bounding_box(0,0,box_left) || !bh->bounding_box(0,0,box_right))
    {
        std::cerr << "no bounding box in bvh_node z_compare" << std::endl;
    }
    if(box_left.min().z() - box_right.min().z() < 0.0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

//===================================================================
bvh_node::bvh_node()
{

}

//===================================================================
bvh_node::bvh_node(surface **l, int n, float time0, float time1)
{
    //choose an axis to sort surface by randomly
    int axis = int(3*unit_random());

    if(axis == 0)
    {
        std::qsort(l,n,sizeof(surface *),box_x_compare);
    }
    else if(axis == 1)
    {
        std::qsort(l,n,sizeof(surface *),box_y_compare);
    }
    else
    {
        std::qsort(l,n,sizeof(surface *),box_z_compare);
    }

    //construct node recursivly
    if(n == 1)
    {
        left  = l[0];
        right = l[0];
    }
    else if(n == 2)
    {
        left  = l[0];
        right = l[1];
    }
    else
    {
        left  = new bvh_node(l,n/2,time0, time1);
        right = new bvh_node(l + n/2, n - n/2, time0, time1);
    }

    //check bounding box exists
    aabb box_left, box_right;
    if(!left->bounding_box(time0,time1, box_left) ||
            !right->bounding_box(time0,time1, box_right))
    {
        std::cerr << "no bounding box in bvh_node constructor" << std::endl;
    }

    box = box_left.surrounding_box(box_left, box_right);
}

//===================================================================
bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
    //check if ray intersects bounding box
    if(box.hit(r, t_min, t_max))
    {

        hit_record left_rec, right_rec;
        bool hit_left  = left->hit(r, t_min, t_max, left_rec);
        bool hit_right = right->hit(r, t_min, t_max, right_rec);
        //if ray intersects both bounding boxes, uses ray with shortest ray
        if(hit_left && hit_right)
        {
            if(left_rec.t < right_rec.t)
            {
                rec = left_rec;
            }
            else
            {
                rec = right_rec;
            }
            return true;
        }
        //otherwise return which node was intresected
        else if(hit_left)
        {
            rec = left_rec;
            return true;
        }
        else if(hit_right)
        {
            rec = right_rec;
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}

//===================================================================
bool bvh_node::bounding_box(float t0, float t1, aabb& box) const
{
    box = this->box;
    return true;
}


