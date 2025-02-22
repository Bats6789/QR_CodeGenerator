#ifndef __QRCODE_H__
#define __QRCODE_H__

#include <stdbool.h>
#include <stddef.h>

#include "image.h"

#define MODULE_SZ 21
#define QR_SZ (MODULE_SZ + 8)
#define PIXEL_PER_MODULE 14
#define QR_VERSION 1

#define ERROR_CORRECTION 1
#define MASK 0
#define FORMAT_VAL ((ERROR_CORRECTION << 3) + (MASK))

#define FORMAT_XOR_MASK 0b101010000010010

typedef struct QRcode_t {
    size_t width;
    size_t height;
    bool *modules;
} QRcode_t;

QRcode_t generate_QRcode(const char *message);
image_t QRcodeToImage(QRcode_t QRcode);

#endif /* end of header guard: __QRCODE_H__ */
