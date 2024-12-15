#include "utils.h"

// Genera un numero casuale tra 0 e 1
double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Genera un numero casuale tra 0 e 1
double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}