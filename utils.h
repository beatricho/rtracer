#ifndef UTILS_H
#define UTILS_H
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    double x;
    double y;
    double z;
} vec3;

typedef struct {
    vec3 orig;
    vec3 dir;
} ray;

// Genera un numero casuale tra 0 e 1
double random_double();
// Genera un numero casuale tra 0 e 1
double random_double_range(double min, double max);
 #endif