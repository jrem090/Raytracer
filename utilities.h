#ifndef UTILITIES_H
#define UTILITIES_H

#include "vec3.h"

// This gheader file defines utility functions
// to be used throughout the raytracer

/**
 * @brief unit_random
 * @return returns a vlue between 0.30 and 1.0 inclusive
 */
float unit_random();

/**
 * @brief random_in_unit_disk
 * This method returns a random value inside of a unit disk centered around 0,0
 * @return vec3 representing a point on a unit disj
 */
vec3 random_in_unit_disk();

/**
 * @brief random_in_unit_sphere
 * @return returns a vec3 inside of a unit sphere
 */
vec3 random_in_unit_sphere();

/**
 * @brief reflect reflects a ray v using the normal n
 * @param v ray to be reflected
 * @param n normal of the reflecting surface
 * @return
 */
vec3 reflect(const vec3& v, const vec3& n);

/**
 * @brief refract
 * @param v input vector
 * @param n normal
 * @param ni_over_nt refractive index
 * @param refracted refracted vector
 * @return if vector was fefracted ot not
 */
bool refract(const vec3& v,
             const vec3& n,
             float ni_over_nt,
             vec3& refracted);

#endif // UTILITIES_H
