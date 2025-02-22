#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stddef.h>
#include <stdint.h>

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

typedef struct image {
    size_t height;
    size_t width;
    pixel_t *pixels;
} image_t;

// allocation
image_t init_image(size_t width, size_t height);

// deallocation
void free_image(image_t image);

#endif /* end of header guard: __IMAGE_H__ */
