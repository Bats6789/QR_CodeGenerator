#include "image_export.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    printf("Hello World\n");
    size_t width = 300;
    size_t height = 300;
	image_t image;

	image = init_image(width, height);
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j) {
			image.pixels[i * width + j].red = i < height / 2 && j < width / 2 ? 255 : 0;
			image.pixels[i * width + j].green = i < height / 2 && j >= width / 2 ? 255 : 0;
			image.pixels[i * width + j].blue = i >= height / 2 && j < width / 2 ? 255 : 0;
			image.pixels[i * width + j].alpha = 255;
		}
	}

	if (export_to_png("test.png", image) != 0) {
		perror("export");
		return EXIT_FAILURE;
	}

	free_image(image);

    return 0;
}
