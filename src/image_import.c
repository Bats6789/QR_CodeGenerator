#include <png.h>
#include <pngconf.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "image_import.h"

image_t import_image(const char *filename) {
    image_t image = {0, 0, NULL};

    image = import_png(filename);

    return image;
}

image_t import_png(const char *filename) {
    image_t image = {0, 0, NULL};
    FILE *file;
    unsigned char sig[8];
    png_structp png;
    png_infop info;
    png_uint_32 width;
    png_uint_32 height;
    int bit_depth;
    int color_type;
    png_uint_32 rowbytes;

    file = fopen(filename, "rb");
    if (file == NULL) {
        return image;
    }

    fread(sig, 1, 8, file);
    if (!png_check_sig(sig, 8)) {
        return image;
    }

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        return image;
    }

    info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, NULL, NULL);
        return image;
    }

    png_init_io(png, file);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    png_get_IHDR(png, info, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

    image = init_image(width, height);
    if (image.pixels == NULL) {
        png_destroy_read_struct(&png, &info, NULL);
        return image;
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_expand(png);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand(png);
    }
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_expand(png);
    }

    if (bit_depth == 16) {
        png_set_strip_16(png);
    }
    if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
        png_set_gray_to_rgb(png);
    }

    png_bytep row_pointers[height];
    int channels;
    unsigned char *image_data;

    png_read_update_info(png, info);

    rowbytes = png_get_rowbytes(png, info);
    channels = png_get_channels(png, info);

    image_data = malloc(rowbytes * height);

    for (size_t i = 0; i < height; ++i) {
        row_pointers[i] = image_data + i * rowbytes;
    }

    png_read_image(png, row_pointers);

    png_read_end(png, info);

    png_destroy_read_struct(&png, &info, NULL);
    fclose(file);

    for (size_t i = 0; i < image.width * image.height; ++i) {
        image.pixels[i].red = image_data[channels * i];
        image.pixels[i].green = image_data[channels * i + 1];
        image.pixels[i].blue = image_data[channels * i + 2];
        image.pixels[i].alpha = channels == 4 ? image_data[channels * i + 3] : 255;
    }

    free(image_data);

    return image;
}
