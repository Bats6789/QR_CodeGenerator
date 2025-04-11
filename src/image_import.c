#include <ctype.h>
#include <png.h>
#include <pngconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <string.h>

#include "image.h"
#include "image_import.h"

struct jpeg_error_t {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

typedef struct jpeg_error_t *my_error_ptr;

image_t import_image(const char *filename) {
    image_t image = {0, 0, NULL};
	const char *dot = strrchr(filename, '.');
	char ext[5];

	if (!dot || dot == filename) {
		return image;
	}

	dot++;

	for (size_t i = 0; i < 5; ++i) {
		ext[i] = tolower(dot[i]);
		if (ext[i] == '\0') {
			break;
		}
	}

	if (strcmp(ext, "png") == 0) {
		image = import_png(filename);
	} else if (strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) {
		image = import_jpeg(filename);
	}

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

METHODDEF(void) jpeg_error_callback(j_common_ptr cinfo) {
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	(*cinfo->err->output_message) (cinfo);

	longjmp(myerr->setjmp_buffer, 1);
}

image_t import_jpeg(const char *filename) {
	image_t image = {0, 0, NULL};
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_t jerr;
	FILE *file;
	JSAMPARRAY buffer;
	int row_stride;

	file = fopen(filename, "rb");
	if (file == NULL) {
		return image;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = jpeg_error_callback;

	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(file);
		if (image.pixels != NULL) {
			free_image(image);
		}
		return (image_t){0, 0, NULL};
	}

	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, file);

	(void) jpeg_read_header(&cinfo, TRUE);

	// force output colorspace to always be RGB
	cinfo.out_color_space = JCS_RGB;

	(void) jpeg_start_decompress(&cinfo);

	image = init_image(cinfo.output_width, cinfo.output_height);

	row_stride = cinfo.output_width * cinfo.output_components;

	buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	while (cinfo.output_scanline < cinfo.output_height) {
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		size_t row = (cinfo.output_scanline - 1) * image.width;
		for (size_t i = 0; i < image.width; ++i) {
			image.pixels[row + i].red = buffer[0][3 * i];
			image.pixels[row + i].green = buffer[0][3 * i + 1];
			image.pixels[row + i].blue = buffer[0][3 * i + 2];
			image.pixels[row + i].alpha = 255;
		}
	}

	jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	fclose(file);

	return image;
}
