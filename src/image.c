#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

static uint8_t tohex(char c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}

	return tolower(c) - 'a' + 10;
}

image_t init_image(size_t width, size_t height) {
    image_t image = {height, width, NULL};

    image.pixels = malloc(sizeof *image.pixels * width * height);

    return image;
}

// deallocation
void free_image(image_t image) { free(image.pixels); }

// color
pixel_res_t str_to_color(const char *str) {
	pixel_res_t pixel = {{ .color=0 }, false };

	if (strlen(str) != 6) {
		return pixel;
	}

	for (size_t i = 0; i < 6; ++i) {
		if (!(('0' <= str[i] && str[i] <= '9') || ('a' <= tolower(str[i]) && tolower(str[i]) <= 'f'))) {
			return pixel;
		}
	}

	pixel.pixel.red = (tohex(str[0]) << 4) + tohex(str[1]);
	pixel.pixel.green = (tohex(str[2]) << 4) + tohex(str[3]);
	pixel.pixel.blue = (tohex(str[4]) << 4) + tohex(str[5]);
	pixel.pixel.alpha = 0xFF;
	pixel.valid = true;

	return pixel;
}
