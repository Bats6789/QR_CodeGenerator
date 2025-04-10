#include <ctype.h>
#include <math.h>
#include <stdio.h>
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
    pixel_res_t pixel = {{.color = 0}, false};

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

pixel_t get_avg_color(image_t image, point_t start, point_t stop) {
    size_t red_sum = 0;
    size_t green_sum = 0;
    size_t blue_sum = 0;
    size_t alpha_sum = 0;
    size_t count = 0;
    pixel_t pixel;
    point_t loc;

    for (loc.y = start.y; loc.y < stop.y; ++loc.y) {
        for (loc.x = start.x; loc.x < stop.x; ++loc.x) {
            pixel = get_color(image, loc);
            red_sum += (size_t)pixel.red;
            green_sum += (size_t)pixel.green;
            blue_sum += (size_t)pixel.blue;
            alpha_sum += (size_t)pixel.alpha;
            count++;
        }
    }

    pixel.red = red_sum / count;
    pixel.green = green_sum / count;
    pixel.blue = blue_sum / count;
    pixel.alpha = alpha_sum / count;

    return pixel;
}

void fill_color(image_t image, pixel_t color, point_t start, point_t stop) {
    point_t loc;
    for (loc.y = start.y; loc.y < stop.y; ++loc.y) {
        for (loc.x = start.x; loc.x < stop.x; ++loc.x) {
            color_pixel(image, color, loc);
        }
    }
}

void color_pixel(image_t image, pixel_t color, point_t loc) { image.pixels[loc.y * image.width + loc.x] = color; }

pixel_t get_color(image_t image, point_t loc) { return image.pixels[loc.y * image.width + loc.x]; }

pixel_t blend_pixel_by_alpha(pixel_t bottom_pixel, pixel_t top_pixel) {
    pixel_t res;
    pixel_t bp = bottom_pixel;
    pixel_t tp = top_pixel;
	double b_alpha = bottom_pixel.alpha / 255.0;
	double t_alpha = top_pixel.alpha / 255.0;
    double bp_alpha_val;
	double new_alpha;

    bp_alpha_val = b_alpha * (1.0 - t_alpha);

    new_alpha = t_alpha + bp_alpha_val;

    res.red = round((tp.red * t_alpha + bp.red * bp_alpha_val) / new_alpha);
    res.green = round((tp.green * t_alpha + bp.green * bp_alpha_val) / new_alpha);
    res.blue = round((tp.blue * t_alpha + bp.blue * bp_alpha_val) / new_alpha);
	res.alpha = 255 * round(new_alpha);

    return res;
}

int embed_img(image_t main_image, image_t embed_image, point_t start_embed_pt, point_t stop_embed_pt) {
    size_t height_ratio;
    size_t width_ratio;
    point_t avg_start;
    point_t avg_stop;
    point_t main_loc;
    pixel_t avg_color;
    pixel_t blend_color;

    if (embed_image.pixels == NULL || main_image.pixels == NULL) {
        return EXIT_FAILURE;
    }

    if (start_embed_pt.x >= stop_embed_pt.x || start_embed_pt.y >= stop_embed_pt.y) {
        return EXIT_FAILURE;
    }

	if (embed_image.width >= embed_image.height) {
		width_ratio = embed_image.width / (stop_embed_pt.x - start_embed_pt.x);
		height_ratio = embed_image.height * ((double)width_ratio / embed_image.width);
	} else {
		height_ratio = embed_image.height / (stop_embed_pt.y - start_embed_pt.y);
		width_ratio = embed_image.width * ((double)height_ratio / embed_image.height);
	}

    main_loc = start_embed_pt;

    for (size_t row = 0; row < embed_image.height; row += height_ratio) {
		avg_start.y = row;

		if (avg_start.y + height_ratio > embed_image.height) {
			avg_stop.y = embed_image.height - 1;
		} else {
			avg_stop.y = avg_start.y + height_ratio;
		}

        for (size_t col = 0; col < embed_image.width; col += width_ratio) {
            avg_start.x = col;

			if (avg_start.x + width_ratio > embed_image.width) {
				avg_stop.x = embed_image.width - 1;
			} else {
				avg_stop.x = avg_start.x + width_ratio;
			}

            avg_color = get_avg_color(embed_image, avg_start, avg_stop);
            blend_color = blend_pixel_by_alpha(get_color(main_image, main_loc), avg_color);
            color_pixel(main_image, blend_color, main_loc);

            main_loc.x++;
        }
        main_loc.x = start_embed_pt.x;
        main_loc.y++;
    }

    return EXIT_SUCCESS;
}
