#ifndef RAY_H
#define RAY_H
#include "utils.h"

vec3 *at(double t, ray* r);
vec3 *ray_color(ray r);
#endif