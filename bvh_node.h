#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "surface.h"
#include "aabb.h"

class bvh_node : public surface
{
public:
    bvh_node();
    bvh_node(surface **l, int n, float time0, float time1);
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0, float t1, aabb& box) const;

    surface *left;
    surface *right;
    aabb box;
};

#endif // BVH_NODE_H
