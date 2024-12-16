#include "utils.h"
#include "ray.h"
#include "vec3.h"

int main() {

    // Image

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width/image_height);
    vec3 camera_center = {0, 0, 0}; //doveva essere un point3

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = {viewport_width, 0, 0};
    vec3 viewport_v = {0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = *divide(&viewport_u, image_width);
    vec3 pixel_delta_v = *divide(&viewport_v, image_height);

    // Calculate the location of the upper left pixel.
    vec3 temp = {0, 0, focal_length};
    vec3 viewport_upper_left = *subtract(subtract(subtract(&camera_center, &temp), &(*divide(&viewport_u,2))), &(*divide(&viewport_u,2)));
    vec3 pixel00_loc = *mul(sum(&viewport_upper_left, 0.5), add(&pixel_delta_u, &pixel_delta_v));

    // Render
    char* output= "./out.ppm";

    FILE *fd;
    fd = fopen(output, "w");
    if (fd == NULL)
    {
        perror("Errore in apertura del file");
        exit(1);
    }
    fprintf(fd, "P3\n");
    fprintf(fd, "%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        printf("\nScanlines remaining: %d", image_height-j);
        for (int i = 0; i < image_width; i++) {
            vec3 pixel_center = *add(add(&pixel00_loc, multiply(&pixel_delta_u, i)), multiply(&pixel_delta_v, j));
            vec3 ray_direction = *subtract(&pixel_center, &camera_center);
            ray r = {camera_center, ray_direction};

            vec3 pixel_color = *ray_color(r);
            //vec3 pixel_color = {(double)i/(image_width-1), (double)j/(image_height-1), 0};
            write_color(fd, pixel_color);
        }
    }

    /* chiude il file */
    fclose(fd);

    printf("\nDone.\n");
}