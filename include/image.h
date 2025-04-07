#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define WHITE ((union pixel){.red = 0xFF, .green = 0xFF, .blue = 0xFF, .alpha = 0xFF})
#define BLACK ((union pixel){.red = 0x00, .green = 0x00, .blue = 0x00, .alpha = 0xFF})

typedef union pixel {
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    };
    uint32_t color;
} pixel_t;

typedef struct pixel_res_t {
	pixel_t pixel;
	bool valid;
} pixel_res_t;

typedef struct image {
    size_t height;
    size_t width;
    pixel_t *pixels;
} image_t;

typedef struct point {
	size_t x;
	size_t y;
} point_t;

// allocation
image_t init_image(size_t width, size_t height);

// deallocation
void free_image(image_t image);

// color
pixel_res_t str_to_color(const char *str);
pixel_t get_avg_color(image_t image, point_t start, point_t stop);
void fill_color(image_t image, pixel_t color, point_t start, point_t stop);
void color_pixel(image_t image, pixel_t color, point_t loc);
pixel_t get_color(image_t image, point_t loc);
pixel_t blend_pixel_by_alpha(pixel_t p1, pixel_t p2);

// image manipulation
int embed_img(image_t main_image, image_t embed_image, point_t start_embed_pt, point_t stop_embed_pt);

#endif /* end of header guard: __IMAGE_H__ */
