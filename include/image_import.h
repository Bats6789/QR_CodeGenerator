#ifndef __IMAGE_IMPORT_H__
#define __IMAGE_IMPORT_H__

#include "image.h"

image_t import_image(const char *filename);

image_t import_png(const char *filename);

image_t import_jpeg(const char *filename);

#endif /* end of header guard: __IMAGE_IMPORT_H__ */
