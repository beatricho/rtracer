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
            vec3 pixel_color = {(double)i/(image_width-1), (double)j/(image_height-1), 0};
            write_color(fd, pixel_color);
        }
    }

    /* chiude il file */
    fclose(fd);

    printf("Done.\n");
}