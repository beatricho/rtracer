#ifndef VEC3_H
#define VEC3_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "ray.h"

vec3 *add(vec3 *one, vec3 *two);
vec3 *subtract(vec3 *one, vec3 *two);
vec3 *multiply(vec3 *one, double two);
vec3 *divide(vec3 *one, double two);
double length(vec3 *one);
bool near_zero( vec3 *v);
vec3 *random_vec3();
vec3 *random_vec3_range(double min, double max);
vec3 *cross( vec3 *u,  vec3 *v);
vec3 *unit_vector( vec3 *v);
vec3 *random_in_unit_disk();
vec3 *random_unit_vector();
vec3 *random_on_hemisphere( vec3 *normal);
vec3 *reflect( vec3 *v,  vec3 *n);
vec3 *refract( vec3 *uv,  vec3 *n, double etai_over_etat);
double length_squared( vec3 *one);
void write_color(FILE* out, vec3 pixel_color);
#endif