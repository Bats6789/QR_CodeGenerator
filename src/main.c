#include <ctype.h>
#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int gf_log[256];
int gf_exp[512];

void calculate_table(void) {
    int x = 1;
    size_t i;
    for (i = 0; i < 255; ++i) {
        gf_exp[i] = x;
        gf_log[x] = i;

        if ((x & 0x80) == 0x80) {
            x <<= 1;
            x ^= 0x11D;
            x &= 0xFF;
        } else {
            x <<= 1;
        }
    }

    for (; i < 512; ++i) {
        gf_exp[i] = gf_exp[i - 255];
    }
}

int *generate_poly(size_t sz) {
	int *poly = NULL;
	int *tmp_poly = NULL;
	int a_n = gf_exp[sz - 1];
	size_t poly_sz = sz + 1;

	poly = calloc(poly_sz, sizeof *poly);

	if (sz == 1) {
		poly[1] = 1;
		return poly;
	}

	tmp_poly = generate_poly(sz - 1);

	for (size_t i = 0; i < sz; ++i) {
		poly[i] ^= gf_exp[gf_log[tmp_poly[i]] + gf_log[1]];
		poly[i + 1] ^= gf_exp[gf_log[tmp_poly[i]] + gf_log[a_n]];
	}

	free(tmp_poly);

	return poly;
}

size_t reed_solomon(size_t data_sz, int data[data_sz], size_t ec_sz, int **error_correction) {
    int *ec = malloc(sizeof *ec * ec_sz);
    int *buf = calloc(data_sz + ec_sz, sizeof *buf);
    int *gp = generate_poly(ec_sz);

    memcpy(buf, data, sizeof *data * data_sz);

    for (size_t i = 0; i < data_sz; ++i) {
        int coef = buf[i];
        for (size_t j = 1; j < ec_sz + 1; ++j) {
            buf[i + j] ^= gf_exp[gf_log[gp[j]] + gf_log[coef]];
        }
    }

    memcpy(ec, buf + data_sz, sizeof *ec * ec_sz);
    *error_correction = ec;

	free(buf);
	free(gp);

    return ec_sz;
}

int alphanumeric_lookup(char c) {
	if (isdigit(c)) {
		return c - '0';
	} else if (isalpha(c)) {
		return toupper(c) - 'A' + 10;
	} else {
		switch (c) {
			case ' ':
				return 36;
			case '$':
				return 37;
			case '%':
				return 38;
			case '*':
				return 39;
			case '+':
				return 40;
			case '-':
				return 41;
			case '.':
				return 42;
			case '/':
				return 43;
			case ':':
				return 44;
		}
	}
	return -1;
}

size_t generate_codewords(const char *message, int **codewords) {
	size_t sz = 19;
	int mode = 0b0010; // alphanumeric
	int *data = calloc(sz, sizeof *data);
	size_t byte_loc = 4;
	size_t data_loc = 0;
	size_t mes_len = strlen(message);

	uint8_t byte;
	uint16_t tmp;

	byte = mode;
	byte <<=4;
	byte ^= (mes_len & 0x1FF) >> 5;

	data[data_loc++] = ((int)byte) & 0xFF;

	byte = mes_len & 0x1F;
	byte_loc = 5;

	while (*message) {
		int val1 = alphanumeric_lookup(*message);
		int val2 = alphanumeric_lookup(*(message + 1));

		if (val2 == -1) {
			int rem_bits = 8 - byte_loc;
			if (rem_bits >= 6) {
				byte <<= 6;
				byte ^= val1;
				byte_loc += 6;
				if (byte_loc == 8) {
					data[data_loc++] = ((int)byte) & 0xFF;
					byte = 0;
					byte_loc = 0;
				}
			} else {
				byte <<= rem_bits;
				byte ^= val1 >> (6 - rem_bits);
				data[data_loc++] = ((int)byte) & 0xFF;
				byte = val1 & (0x3F >> rem_bits);
				byte_loc = 6 - rem_bits;
			}
			message++;
		} else {
			tmp = val1 * 45 + val2;
			int rem_bits = 8 - byte_loc;
			byte <<= rem_bits;
			byte ^= tmp >> (11 - rem_bits);
			int rem_tmp_bits = 11 - rem_bits;
			data[data_loc++] = ((int)byte) & 0xFF;
			if (rem_tmp_bits > 8) {
				byte = ((tmp & (0x7FF >> (11 - rem_tmp_bits))) >> (rem_tmp_bits - 8)) & 0xFF;
				data[data_loc++] = ((int)byte) & 0xFF;
				rem_tmp_bits -= 8;
			}
			byte = tmp & (0xFF >> (8 - rem_tmp_bits));
			byte_loc = rem_tmp_bits;
			message += 2;
		}
	}

	if (byte_loc <= 4) {
		byte <<= 4;
		byte <<= (4 - byte_loc);
		data[data_loc++] = ((int)byte) & 0xFF;
	} else {
		byte <<= (8 - byte_loc);
		data[data_loc++] = ((int)byte) & 0xFF;
		byte = 0;
		data[data_loc++] = ((int)byte) & 0xFF;
	}
	int count = 0;

	for (; data_loc < sz; ++data_loc) {
		if ((count & 1) == 1) {
			data[data_loc] = 0b11101100;
		} else {
			data[data_loc] = 0b00010001;
		}
		count += 1;
	}

	*codewords = data;

	return sz;
}

int main(int argc, char **argv) {
    printf("Hello World: %d\n", 0b10);
    size_t width = QR_SZ * PIXEL_PER_MODULE;
    size_t height = QR_SZ * PIXEL_PER_MODULE;
    image_t image;
    pixel_t pixel = WHITE;
    int *ec;
    size_t ec_sz;
    int *data = NULL;
	size_t data_sz = generate_codewords("Blake Wingard", &data);

    calculate_table();
    ec_sz = reed_solomon(data_sz, data, 7, &ec);

    for (size_t i = 0; i < data_sz; ++i) {
        printf("0x%X ", data[i]);
    }
    putchar('\n');
    for (size_t i = 0; i < ec_sz; ++i) {
        printf("0x%X ", ec[i]);
    }
    putchar('\n');

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
                (((mod_row == 0 || mod_row == 6) && (mod_col < 7 || mod_col >= MODULE_SZ - 7)) ||
                 ((mod_row == MODULE_SZ - 7 || mod_row == MODULE_SZ - 1) && mod_col < 7) ||
                 ((mod_row < 7 || mod_row >= MODULE_SZ - 7) && (mod_col == 0 || mod_col == 6)) ||
                 (mod_row < 7 && (mod_col == MODULE_SZ - 7 || mod_col == MODULE_SZ - 1)) ||
                 ((2 <= mod_row && mod_row <= 4) &&
                  ((2 <= mod_col && mod_col <= 4) || (MODULE_SZ - 5 <= mod_col && mod_col <= MODULE_SZ - 3))) ||
                 ((MODULE_SZ - 5 <= mod_row && mod_row <= MODULE_SZ - 3) && (2 <= mod_col && mod_col <= 4)) ||
                 (mod_row == 6 && (7 < mod_col && mod_col < MODULE_SZ - 8) && (mod_col - 8) % 2 == 0) ||
                 (mod_col == 6 && (7 < mod_row && mod_row < MODULE_SZ - 8) && (mod_row - 8) % 2 == 0))) {
                pixel = BLACK;
            }

            // format
            if ((mod_col == 8 && mod_row == 4 * QR_VERSION + 9) ||  // Dark Module
                ((format & 0x1) == 0x1 &&
                 ((mod_row == 0 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 1))) ||  // 0
                ((format & 0x2) == 0x2 &&
                 ((mod_row == 1 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 2))) ||  // 1
                ((format & 0x4) == 0x4 &&
                 ((mod_row == 2 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 3))) ||  // 2
                ((format & 0x8) == 0x8 &&
                 ((mod_row == 3 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 4))) ||  // 3
                ((format & 0x10) == 0x10 &&
                 ((mod_row == 4 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 5))) ||  // 4
                ((format & 0x20) == 0x20 &&
                 ((mod_row == 5 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 6))) ||  // 5
                ((format & 0x40) == 0x40 &&
                 ((mod_row == 7 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 7))) ||  // 6
                ((format & 0x80) == 0x80 &&
                 ((mod_row == 8 && mod_col == 8) || (mod_row == 8 && mod_col == MODULE_SZ - 8))) ||  // 7
                ((format & 0x100) == 0x100 &&
                 ((mod_row == 8 && mod_col == 7) || (mod_row == MODULE_SZ - 7 && mod_col == 8))) ||  // 8
                ((format & 0x200) == 0x200 &&
                 ((mod_row == 8 && mod_col == 5) || (mod_row == MODULE_SZ - 6 && mod_col == 8))) ||  // 9
                ((format & 0x400) == 0x400 &&
                 ((mod_row == 8 && mod_col == 4) || (mod_row == MODULE_SZ - 5 && mod_col == 8))) ||  // 10
                ((format & 0x800) == 0x800 &&
                 ((mod_row == 8 && mod_col == 3) || (mod_row == MODULE_SZ - 4 && mod_col == 8))) ||  // 11
                ((format & 0x1000) == 0x1000 &&
                 ((mod_row == 8 && mod_col == 2) || (mod_row == MODULE_SZ - 3 && mod_col == 8))) ||  // 12
                ((format & 0x2000) == 0x2000 &&
                 ((mod_row == 8 && mod_col == 1) || (mod_row == MODULE_SZ - 2 && mod_col == 8))) ||  // 13
                ((format & 0x4000) == 0x4000 &&
                 ((mod_row == 8 && mod_col == 0) || (mod_row == MODULE_SZ - 1 && mod_col == 8)))) {  // 14
                pixel = BLACK;
            }

            for (size_t row = i * PIXEL_PER_MODULE; row < (i + 1) * PIXEL_PER_MODULE; ++row) {
                for (size_t col = j * PIXEL_PER_MODULE; col < (j + 1) * PIXEL_PER_MODULE; ++col) {
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
