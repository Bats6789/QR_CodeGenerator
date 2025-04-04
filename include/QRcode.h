#ifndef __QRCODE_H__
#define __QRCODE_H__

#include <stdbool.h>
#include <stddef.h>

#include "image.h"

#define PIXEL_PER_MODULE 14

#define ERROR_CORRECTION 1
#define MASK 0
#define FORMAT_VAL ((ERROR_CORRECTION << 3) + (MASK))

#define FORMAT_XOR_MASK 0b101010000010010

typedef enum QR_recovery_t {
    QR_L = 0b01,  // 7%
    QR_M = 0b00,  // 15%
    QR_Q = 0b11,  // 25%
    QR_H = 0b10   // 30%
} QR_recovery_t;

typedef enum QR_mask_t {
    MASK_0 = 0b000,
    MASK_1 = 0b001,
    MASK_2 = 0b010,
    MASK_3 = 0b011,
    MASK_4 = 0b100,
    MASK_5 = 0b101,
    MASK_6 = 0b110,
    MASK_7 = 0b111,
    M_MASK_0 = 0b00,
    M_MASK_1 = 0b01,
    M_MASK_2 = 0b10,
    M_MASK_3 = 0b11,
	ANY_MASK = -1
} QR_mask_t;

typedef enum QR_version_t {
    V1 = 1,
    V2 = 2,
    V3 = 3,
    V4 = 4,
    V5 = 5,
    V6 = 6,
    V7 = 7,
    V8 = 8,
    V9 = 9,
    V10 = 10,
    V11 = 11,
    V12 = 12,
    V13 = 13,
    V14 = 14,
    V15 = 15,
    V16 = 16,
    V17 = 17,
    V18 = 18,
    V19 = 19,
    V20 = 20,
    V21 = 21,
    V22 = 22,
    V23 = 23,
    V24 = 24,
    V25 = 25,
    V26 = 26,
    V27 = 27,
    V28 = 28,
    V29 = 29,
    V30 = 30,
    V31 = 31,
    V32 = 32,
    V33 = 33,
    V34 = 34,
    V35 = 35,
    V36 = 36,
    V37 = 37,
    V38 = 38,
    V39 = 39,
    V40 = 40,
    MV1 = 41,
    MV2 = 42,
    MV3 = 43,
    MV4 = 44,
	ANY_VERSION = 45,
	INVALID_VERSION = -1
} QR_version_t;

typedef struct module_t {
    bool data;
    bool used;
} module_t;

typedef struct QRcode_t {
    size_t width;
    size_t height;
    module_t *modules;
} QRcode_t;

typedef struct QRblock_t {
	size_t data_sz;
	size_t err_sz;
} QRblock_t;

typedef struct QR_version_params_t {
	size_t block_count;
	QRblock_t blocks[81];
} QR_version_params_t;

typedef struct format {
	size_t pixel_per_module;
	pixel_t background;
	pixel_t foreground;
} format_t;

QRcode_t generate_QRcode(const char *message, QR_version_t version, QR_mask_t mask, QR_recovery_t recovery);
image_t QRcodeToImage(QRcode_t QRcode, format_t format);
uint16_t get_format(QR_recovery_t recovery, QR_mask_t mask);
uint32_t get_version(QR_version_t version);
QR_version_params_t get_version_params(QR_version_t QR_version, QR_recovery_t recover);
size_t get_QR_size(QR_version_t QR_version);
QR_version_t get_minimum_version(size_t data_sz, QR_recovery_t recovery);

#endif /* end of header guard: __QRCODE_H__ */
