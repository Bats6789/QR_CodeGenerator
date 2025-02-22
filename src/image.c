#include <stdlib.h>

#include "image.h"

image_t init_image(size_t width, size_t height) {
    image_t image = {height, width, NULL};

    image.pixels = malloc(sizeof *image.pixels * width * height);

    return image;
}

// deallocation
void free_image(image_t image) { free(image.pixels); }
