#include "vec3.h"

vec3 *add(vec3 *one, vec3 *two)
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = one->x + two->x;
    result->y = one->y + two->y;
    result->z = one->z + two->z;
    return result;
}
vec3 *subtract(vec3 *one, vec3 *two)
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = one->x - two->x;
    result->y = one->y - two->y;
    result->z = one->z - two->z;
    return result;
}
vec3 *multiply(vec3 *one, double two)
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = one->x * two;
    result->y = one->y * two;
    result->z = one->z * two;
    return result;
}
vec3 *divide(vec3* one, double two)
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = one->x / two;
    result->y = one->y / two;
    result->z = one->z / two;
    return result;
}
double length(vec3 *one)
{
    return sqrt(length_squared(one));
}

double length_squared(vec3 *one)
{
    double result = one->x * one->x + one->y * one->y + one->z * one->z;
    return result;
}

// Restituisce true se il vettore è vicino a zero in tutte le dimensioni
bool near_zero(vec3 *v)
{
    double s = 1e-8; // Soglia di tolleranza
    return (fabs(v->x) < s) && (fabs(v->y) < s) && (fabs(v->z) < s);
}

// Genera un vettore con componenti casuali tra 0 e 1
vec3 *random_vec3()
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = random_double();
    result->y = random_double();
    result->z = random_double();
    return result;
}

// Genera un vettore con componenti casuali tra min e max
vec3 *random_vec3_range(double min, double max)
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = random_double_range(min, max);
    result->y = random_double_range(min, max);
    result->z = random_double_range(min, max);
    return result;
}

double dot(vec3 *u, vec3 *v)
{
    return u->x * v->x + u->y * v->y + u->z * v->z;
}

// Prodotto vettoriale tra due vettori
vec3 *cross(vec3 *u, vec3 *v)
{
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = u->y * v->z - u->z * v->y;
    result->y = u->z * v->x - u->x * v->z;
    result->z = u->x * v->y - u->y * v->x;
    return result;
}

// Restituisce il vettore unitario (normalizzato)
vec3 *unit_vector(vec3 *v)
{
    double len = sqrt(length_squared(v));
    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = v->x / len;
    result->y = v->y / len;
    result->z = v->z / len;
    return result;
}

// Genera un vettore casuale nel disco unitario
vec3 *random_in_unit_disk()
{
    vec3 *p = (vec3 *)malloc(sizeof(vec3));
    while (true)
    {
        p->x = random_double_range(-1, 1);
        p->y = random_double_range(-1, 1);
        p->z = 0;
        if (length_squared(p) < 1)
        {
            return p;
        }
    }
}

// Genera un vettore casuale sulla sfera unitaria
vec3 *random_unit_vector()
{
    vec3 *p = (vec3 *)malloc(sizeof(vec3));
    while (true)
    {
        p->x = random_double_range(-1, 1);
        p->y = random_double_range(-1, 1);
        p->z = random_double_range(-1, 1);
        double len_sq = length_squared(p);
        if (len_sq > 1e-160 && len_sq <= 1.0)
        {
            double len = sqrt(len_sq);
            p->x /= len;
            p->y /= len;
            p->z /= len;
            return p;
        }
    }
}

// Genera un vettore casuale nell'emisfero specificato dal normale
vec3 *random_on_hemisphere(vec3 *normal)
{
    vec3 *on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0)
    {
        return on_unit_sphere; // Nello stesso emisfero del normale
    }
    else
    {
        on_unit_sphere->x = -on_unit_sphere->x;
        on_unit_sphere->y = -on_unit_sphere->y;
        on_unit_sphere->z = -on_unit_sphere->z;
        return on_unit_sphere;
    }
}

// Riflette un vettore rispetto a una normale
vec3 *reflect(vec3 *v, vec3 *n)
{
    double dot_product = 2 * dot(v, n);
    vec3 *scaled_n = (vec3 *)malloc(sizeof(vec3));
    scaled_n->x = n->x * dot_product;
    scaled_n->y = n->y * dot_product;
    scaled_n->z = n->z * dot_product;

    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = v->x - scaled_n->x;
    result->y = v->y - scaled_n->y;
    result->z = v->z - scaled_n->z;

    free(scaled_n);
    return result;
}

// Rifrazione di un vettore attraverso una superficie
vec3 *refract(vec3 *uv, vec3 *n, double etai_over_etat)
{
    double cos_theta = fmin(dot(&(vec3){-uv->x, -uv->y, -uv->z}, n), 1.0);

    vec3 *r_out_perp = (vec3 *)malloc(sizeof(vec3));
    r_out_perp->x = etai_over_etat * (uv->x + cos_theta * n->x);
    r_out_perp->y = etai_over_etat * (uv->y + cos_theta * n->y);
    r_out_perp->z = etai_over_etat * (uv->z + cos_theta * n->z);

    double r_out_parallel_scaling = sqrt(fabs(1.0 - length_squared(r_out_perp)));

    vec3 *r_out_parallel = (vec3 *)malloc(sizeof(vec3));
    r_out_parallel->x = -r_out_parallel_scaling * n->x;
    r_out_parallel->y = -r_out_parallel_scaling * n->y;
    r_out_parallel->z = -r_out_parallel_scaling * n->z;

    vec3 *result = (vec3 *)malloc(sizeof(vec3));
    result->x = r_out_perp->x + r_out_parallel->x;
    result->y = r_out_perp->y + r_out_parallel->y;
    result->z = r_out_perp->z + r_out_parallel->z;

    free(r_out_perp);
    free(r_out_parallel);
    return result;
}

void write_color(FILE* out, vec3 pixel_color)
{
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    fprintf(out, "%d %d %d\n", rbyte, gbyte, bbyte);
}