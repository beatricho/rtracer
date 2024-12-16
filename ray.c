#include "ray.h"
#include "vec3.h"
#include "math.h"

vec3 *at(double t, ray*r) {
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = r->orig.x +r->dir.x*t;
    result->y = r->orig.y +r->dir.y*t;
    result->z = r->orig.x +r->dir.x*t;
        return result;
}

vec3 *ray_color(ray r) {
    vec3 p = {0,0,-1};
    double t = hit_sphere(&p, 1.2, &r);
    if (t > 0.0) {
        vec3 p2 = {0,0,-1};
        vec3 N = *sum(unit_vector(subtract(at(t, &r), &p2)), 1);
        return multiply(&N, 0.5);
    }

    vec3* unit_direction = unit_vector(&r.dir);
    double a = 0.5*(unit_direction->y + 1.0);
    vec3 black = {1.0, 1.0, 1.0};
    vec3 col = {0.5, 0.7, 1.0};

    free(unit_direction);

    return add(multiply(&black, 1.0-a), multiply(&col, a));
}

double hit_sphere(vec3 *center, double radius, ray *r)
{
    vec3 oc = *subtract(center, &r->orig);
    double a = dot(&r->dir, &r->dir);
    double b = -4.0 * dot(&r->dir, &oc);
    double c = dot(&oc, &oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    //printf("\nDiscriminante: %f",discriminant);

    if (discriminant < 0) {
        return -1.0;
    } else {  
        double s = (-b - sqrt(discriminant) ) / (2.0*a);
        //printf("\nRes: %f",s);
        return s;
    }
}