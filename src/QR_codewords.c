#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "QR_codewords.h"
#include "codeword_lookup.h"

size_t generate_codewords(const char *message, int **codewords) {
    int mode = 0b0010;  // alphanumeric
	size_t sz = 100;
    int *data = calloc(sz, sizeof *data);
    size_t byte_loc = 4;
    size_t data_loc = 0;
    size_t mes_len = strlen(message);

    uint8_t byte;
    uint16_t tmp;

    byte = mode;
    byte <<= 4;
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

		if (data_loc + 1 >= sz) {
			sz *= 2;
			data = realloc(data, sizeof *data * sz);
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

	data = realloc(data, sizeof *data * data_loc);

    *codewords = data;

    return data_loc;
}

size_t pad_data(int **codewords, size_t data_sz, size_t desired_sz) {
	int count = 0;
	int *data = *codewords;

	data = realloc(data, sizeof *data * desired_sz);

    for (size_t i = data_sz; i < desired_sz; ++i) {
        if ((count & 1) == 1) {
            data[i] = 0b11101100;
        } else {
            data[i] = 0b00010001;
        }
        count += 1;
    }

	*codewords = data;

	return desired_sz;
}
