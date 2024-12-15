#include "ray.h"

vec3 *at(double t, ray*r) {
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = r->orig.x +r->dir.x*t;
    result->y = r->orig.y +r->dir.y*t;
    result->z = r->orig.x +r->dir.x*t;
        return result;
}

vec3 *ray_color(ray r) {
    vec3* unit_direction = unit_vector(&r.dir);
    double a = 0.5*(unit_direction->y + 1.0);
    vec3 black = {1.0, 1.0, 1.0};
    vec3 col = {0.5, 0.7, 1.0};

    free(unit_direction);

    return add(multiply(&black, 1.0-a), multiply(&col, a));
}