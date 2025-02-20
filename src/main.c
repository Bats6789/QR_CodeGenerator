#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "image_export.h"

#define MODULE_SZ 21
#define QR_SZ (MODULE_SZ + 8)
#define PIXEL_PER_MODULE 14
#define QR_VERSION 1

#define ERROR_CORRECTION 1
#define MASK 0
#define FORMAT_VAL ((ERROR_CORRECTION << 3) + (MASK))

#define FORMAT_XOR_MASK 0b101010000010010

uint16_t BCH(uint16_t data) {
  uint16_t res = 0;
  size_t bit_len = floor(log2(data)) + 1;
  uint16_t poly = 0b0100110111;

  res = data << (10 - bit_len);

  for (size_t i = 0; i < bit_len; ++i) {
    if ((res & 0x200) == 0x200) {
      res <<= 1;
      res ^= poly;
    } else {
      res <<= 1;
    }
    res &= 0x3FF;
  }

  return res;
}

int main(int argc, char **argv) {
  printf("Hello World\n");
  size_t width = QR_SZ * PIXEL_PER_MODULE;
  size_t height = QR_SZ * PIXEL_PER_MODULE;
  image_t image;
  pixel_t pixel = WHITE;

  uint16_t format = ((FORMAT_VAL << 10) + BCH(FORMAT_VAL)) ^ FORMAT_XOR_MASK;
  printf("0b%015B\n", format);

  image = init_image(width, height);

  for (size_t i = 0; i < QR_SZ; ++i) {
    for (size_t j = 0; j < QR_SZ; ++j) {
      // assume white and repaint if not
      pixel = WHITE;
      size_t mod_row = i - 4;
      size_t mod_col = j - 4;

      // finder pattern and timing pattern (Same properties for every QR code)
      if ((4 <= i && mod_row < MODULE_SZ && 4 <= j && mod_col < MODULE_SZ) &&
          (((mod_row == 0 || mod_row == 6) &&
            (mod_col < 7 || mod_col >= MODULE_SZ - 7)) ||
           ((mod_row == MODULE_SZ - 7 || mod_row == MODULE_SZ - 1) &&
            mod_col < 7) ||
           ((mod_row < 7 || mod_row >= MODULE_SZ - 7) &&
            (mod_col == 0 || mod_col == 6)) ||
           (mod_row < 7 &&
            (mod_col == MODULE_SZ - 7 || mod_col == MODULE_SZ - 1)) ||
           ((2 <= mod_row && mod_row <= 4) &&
            ((2 <= mod_col && mod_col <= 4) ||
             (MODULE_SZ - 5 <= mod_col && mod_col <= MODULE_SZ - 3))) ||
           ((MODULE_SZ - 5 <= mod_row && mod_row <= MODULE_SZ - 3) &&
            (2 <= mod_col && mod_col <= 4)) ||
           (mod_row == 6 && (7 < mod_col && mod_col < MODULE_SZ - 8) &&
            (mod_col - 8) % 2 == 0) ||
           (mod_col == 6 && (7 < mod_row && mod_row < MODULE_SZ - 8) &&
            (mod_row - 8) % 2 == 0))) {
        pixel = BLACK;
      }

      // format
      if ((mod_col == 8 && mod_row == 4 * QR_VERSION + 9) || // Dark Module
          ((format & 0x1) == 0x1 &&
           ((mod_row == 0 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 1))) || // 0
          ((format & 0x2) == 0x2 &&
           ((mod_row == 1 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 2))) || // 1
          ((format & 0x4) == 0x4 &&
           ((mod_row == 2 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 3))) || // 2
          ((format & 0x8) == 0x8 &&
           ((mod_row == 3 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 4))) || // 3
          ((format & 0x10) == 0x10 &&
           ((mod_row == 4 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 5))) || // 4
          ((format & 0x20) == 0x20 &&
           ((mod_row == 5 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 6))) || // 5
          ((format & 0x40) == 0x40 &&
           ((mod_row == 7 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 7))) || // 6
          ((format & 0x80) == 0x80 &&
           ((mod_row == 8 && mod_col == 8) ||
            (mod_row == 8 && mod_col == MODULE_SZ - 8))) || // 7
          ((format & 0x100) == 0x100 &&
           ((mod_row == 8 && mod_col == 7) ||
            (mod_row == MODULE_SZ - 7 && mod_col == 8))) || // 8
          ((format & 0x200) == 0x200 &&
           ((mod_row == 8 && mod_col == 5) ||
            (mod_row == MODULE_SZ - 6 && mod_col == 8))) || // 9
          ((format & 0x400) == 0x400 &&
           ((mod_row == 8 && mod_col == 4) ||
            (mod_row == MODULE_SZ - 5 && mod_col == 8))) || // 10
          ((format & 0x800) == 0x800 &&
           ((mod_row == 8 && mod_col == 3) ||
            (mod_row == MODULE_SZ - 4 && mod_col == 8))) || // 11
          ((format & 0x1000) == 0x1000 &&
           ((mod_row == 8 && mod_col == 2) ||
            (mod_row == MODULE_SZ - 3 && mod_col == 8))) || // 12
          ((format & 0x2000) == 0x2000 &&
           ((mod_row == 8 && mod_col == 1) ||
            (mod_row == MODULE_SZ - 2 && mod_col == 8))) || // 13
          ((format & 0x4000) == 0x4000 &&
           ((mod_row == 8 && mod_col == 0) ||
            (mod_row == MODULE_SZ - 1 && mod_col == 8)))) { // 14
        pixel = BLACK;
      }

      for (size_t row = i * PIXEL_PER_MODULE; row < (i + 1) * PIXEL_PER_MODULE;
           ++row) {
        for (size_t col = j * PIXEL_PER_MODULE;
             col < (j + 1) * PIXEL_PER_MODULE; ++col) {
          image.pixels[row * width + col] = pixel;
        }
      }
    }
  }

  if (export_to_png("test.png", image) != 0) {
    perror("export");
    return EXIT_FAILURE;
  }

  free_image(image);

  return 0;
}
