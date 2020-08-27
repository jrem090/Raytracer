#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "surface.h"
#include "aabb.h"

/**
 * @brief The bvh_node class is a tree used to optimize objectlookup
 * for a particular ray.
 */
class bvh_node : public surface
{
public:
    /**
     * @brief bvh_node base constructor
     */
    bvh_node();

    /**
     * @brief bvh_node full constructor
     * @param l pointer to an array of surfaces
     * @param n number of surfaces in the array
     * @param time0 start time
     * @param time1 end time
     */
    bvh_node(surface **l, int n, float time0, float time1);

    /**
     * @brief hit
     * @param r
     * @param t_min
     * @param t_max
     * @param rec
     * @return
     */
    virtual bool hit(const ray& r,
                     float t_min,
                     float t_max,
                     hit_record& rec) const;

    virtual int bvh_hit(const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const;

    /**
     * @brief bounding_box
     * @param t0
     * @param t1
     * @param box
     * @return
     */
    virtual bool bounding_box(float t0, float t1, aabb& box) const;

    //should these be private?
    surface *left;
    surface *right;
    aabb box;
};

#endif // BVH_NODE_H
