#include <png.h>
#include <pngconf.h>
#include <setjmp.h>
#include <stdlib.h>

#include "image_export.h"

// Exports
int export_to_png(const char *filename, image_t image) {
    png_byte *raw_image[image.height];
    FILE *file = NULL;
    png_struct *png = NULL;
    png_info *info = NULL;

    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("test.png");
        return EXIT_FAILURE;
    }

    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);
    if (!png) {
        perror("test.png: write_struct");
        return EXIT_FAILURE;
    }

    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, (png_infopp)NULL);
        return EXIT_FAILURE;
    }

    // png expects to jump when an error occurs
    if (setjmp(png_jmpbuf(png))) {
        perror("test.png: unknown");
        png_destroy_write_struct(&png, &info);
        fclose(file);
        return EXIT_FAILURE;
    }

    // copy image struct to raw image
    for (size_t i = 0; i < image.height; ++i) {
        raw_image[i] = malloc(sizeof *raw_image[i] * 4 * image.width);

        for (size_t j = 0; j < image.width; ++j) {
            raw_image[i][4 * j] = image.pixels[i * image.width + j].red;
            raw_image[i][4 * j + 1] = image.pixels[i * image.width + j].green;
            raw_image[i][4 * j + 2] = image.pixels[i * image.width + j].blue;
            raw_image[i][4 * j + 3] = image.pixels[i * image.width + j].alpha;
        }
    }

    // write png data
    png_init_io(png, file);

    png_set_IHDR(png, info, image.width, image.height, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);

    png_write_image(png, (png_bytepp)raw_image);

    png_write_end(png, NULL);

    // clean up
    png_destroy_write_struct(&png, &info);
	for (size_t i = 0; i < image.height; ++i) {
		free(raw_image[i]);
	}

    fclose(file);

    return EXIT_SUCCESS;
}
