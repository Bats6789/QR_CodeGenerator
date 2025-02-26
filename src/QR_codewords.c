#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "QR_codewords.h"
#include "QRcode.h"
#include "codeword_lookup.h"

size_t generate_codewords(const char *message, int **codewords, QR_version_t version, QR_recovery_t recovery) {
    bool seen_alpha = false;
    bool seen_byte = false;
    size_t len = strlen(message);
    size_t data_sz = 0;

    for (const char *c = message; *c != '\0'; ++c) {
        if (alphanumeric_lookup(*c) == -1) {
            seen_byte = true;
            break;
        }

        if (numeric_lookup(*c) == -1) {
            seen_alpha = true;
        }
    }
    int R;
    int C;
    int M = 4;

    if (seen_byte) {
        C = 16;
        data_sz = (M + C + 8 * len) / 8;
    } else if (seen_alpha) {
        C = 13;
        data_sz = (M + C + 11 * (len / 2) + 6 * (len % 2)) / 8;
    } else {
        switch (len % 3) {
            case 0:
                R = 0;
                break;
            case 1:
                R = 4;
                break;
            default:
                R = 7;
                break;
        }

        C = 14;
        data_sz = (M + C + 10 * (len / 3) + R) / 8;
    }

    if (version == ANY_VERSION) {
        version = get_minimum_version(data_sz, recovery);
    }

    if (seen_byte) {
        return generate_codewords_byte(message, len, codewords, version);
    } else if (seen_alpha) {
        return generate_codewords_alpha(message, len, codewords, version);
    } else {
        return generate_codewords_num(message, len, codewords, version);
    }
}

size_t generate_codewords_byte(const char *message, size_t len, int **codewords, QR_version_t version) {
    int mode = 0b0100;  // alphanumeric
    size_t sz = 100;
    int *data = calloc(sz, sizeof *data);
    size_t byte_loc = 4;
    size_t data_loc = 0;
    size_t count = 0;
	size_t count_len;

    // get count_len
    switch (version) {
        case V1:
        case V2:
        case V3:
        case V4:
        case V5:
        case V6:
        case V7:
        case V8:
        case V9:
            count_len = 8;
            break;
        case V10:
        case V11:
        case V12:
        case V13:
        case V14:
        case V15:
        case V16:
        case V17:
        case V18:
        case V19:
        case V20:
        case V21:
        case V22:
        case V23:
        case V24:
        case V25:
        case V26:
        case V27:
        case V28:
        case V29:
        case V30:
        case V31:
        case V32:
        case V33:
        case V34:
        case V35:
        case V36:
        case V37:
        case V38:
        case V39:
        case V40:
            count_len = 16;
            break;
        case MV3:
            count_len = 4;
            break;
        case MV4:
            count_len = 5;
            break;
        default:
            count_len = 16;
            break;
    }

    uint8_t byte;

    byte = mode;
    byte <<= 4;
    byte ^= (len & ((0x1 << count_len) - 1)) >> (count_len - 4);

    data[data_loc++] = ((int)byte) & 0xFF;
    count_len -= 4;

    if (count_len >= 8) {
        byte = (len & ((0x1 << count_len) - 1) >> (count_len - 8)) & 0xFF;
        count_len -= 8;
        data[data_loc++] = ((int)byte) & 0xFF;
    }

    byte = len & ((0x1 << count_len) - 1);
    byte_loc = count_len;

    while (*message && count < len) {
		int rem_bits = 8 - byte_loc;

		byte <<= rem_bits;
		byte ^= *message >> (8 - rem_bits);
		data[data_loc++] = ((int)byte) & 0xFF;
		byte = *message & (0xFF >> (8 - rem_bits));

		if (data_loc + 1 >= sz) {
			sz *= 2;
			data = realloc(data, sizeof *data * sz);
		}
		message++;
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

size_t generate_codewords_num(const char *message, size_t len, int **codewords, QR_version_t version) {
    int mode = 0b0001;  // numeric
    size_t sz = 100;
    int *data = calloc(sz, sizeof *data);
    size_t byte_loc = 4;
    size_t data_loc = 0;
    size_t count = 0;
    int val1;
    int val2;
    int val3;
    size_t count_len;
    uint8_t byte;
    uint16_t tmp;

    // get count_len
    switch (version) {
        case V1:
        case V2:
        case V3:
        case V4:
        case V5:
        case V6:
        case V7:
        case V8:
        case V9:
            count_len = 10;
            break;
        case V10:
        case V11:
        case V12:
        case V13:
        case V14:
        case V15:
        case V16:
        case V17:
        case V18:
        case V19:
        case V20:
        case V21:
        case V22:
        case V23:
        case V24:
        case V25:
        case V26:
            count_len = 12;
            break;
        case V27:
        case V28:
        case V29:
        case V30:
        case V31:
        case V32:
        case V33:
        case V34:
        case V35:
        case V36:
        case V37:
        case V38:
        case V39:
        case V40:
            count_len = 14;
            break;
        case MV1:
            count_len = 3;
            break;
        case MV2:
            count_len = 4;
            break;
        case MV3:
            count_len = 5;
            break;
        case MV4:
            count_len = 6;
            break;
        default:
            count_len = 14;
            break;
    }

    byte = mode;
    byte <<= 4;
    byte ^= (len & ((0x1 << count_len) - 1)) >> (count_len - 4);

    data[data_loc++] = ((int)byte) & 0xFF;
    count_len -= 4;

    if (count_len >= 8) {
        byte = (len & ((0x1 << count_len) - 1) >> (count_len - 8)) & 0xFF;
        count_len -= 8;
        data[data_loc++] = ((int)byte) & 0xFF;
    }

    byte = len & ((0x1 << count_len) - 1);
    byte_loc = count_len;

    while (*message && count < len) {
        val1 = numeric_lookup(*message);
        val2 = -1;
        val3 = -1;
        if (count + 1 < len) {
            val2 = numeric_lookup(*(message + 1));
        }
        if (count + 2 < len) {
            val3 = numeric_lookup(*(message + 2));
        }

        if (val3 != -1) {
			tmp = val1 * 100 + val2 * 10 + val3;
			int rem_bits = 8 - byte_loc;
			int tmp_bits = 10;

			byte <<= rem_bits;
			byte ^= tmp >> (tmp_bits - rem_bits);
			data[data_loc++] = ((int)byte) & 0xFF;
			tmp_bits -= rem_bits;

			if (tmp_bits >= 8) {
				byte = (tmp & ((0x1 << tmp_bits) - 1)) >> (tmp_bits - 8);
				data[data_loc++] = ((int)byte) & 0xFF;
				tmp_bits -= 8;
				byte = (tmp & ((0x1 << tmp_bits) - 1));
				byte_loc = tmp_bits;
			} else {
				byte = tmp & ((0x1 << tmp_bits) - 1);
				byte_loc = tmp_bits;
			}
			message += 3;
		} else if (val2 != -1) {
			tmp = val1 * 10 + val2;
            int rem_bits = 8 - byte_loc;
			int tmp_bits = 7;

			byte <<= rem_bits;
			if (rem_bits == 8) {
				byte = tmp;
				byte_loc = 7;
			} else {
				byte ^= tmp >> (tmp_bits - rem_bits);
				data[data_loc++] = ((int)byte) & 0xFF;
				tmp_bits -= rem_bits;
				byte = tmp & ((0x1 << tmp_bits) - 1);
				byte_loc = tmp_bits;
			}
			message += 2;
        } else {
            tmp = val1;
            int rem_bits = 8 - byte_loc;
			if (rem_bits <= 4) {
				byte <<= rem_bits;
				byte ^= val1 >> (4 - rem_bits);
				data[data_loc++] = ((int)byte) & 0xFF;
				byte = val1 & (0xF >> rem_bits);
				byte_loc = 4 - rem_bits;
			} else {
				byte <<= 4;
				byte ^= tmp;
				byte_loc += 4;
			}
			message++;
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

size_t generate_codewords_alpha(const char *message, size_t len, int **codewords, QR_version_t version) {
    int mode = 0b0010;  // alphanumeric
    size_t sz = 100;
    int *data = calloc(sz, sizeof *data);
    size_t byte_loc = 4;
    size_t data_loc = 0;
    size_t count = 0;
	size_t count_len;
	int val1;
	int val2;

    // get count_len
    switch (version) {
        case V1:
        case V2:
        case V3:
        case V4:
        case V5:
        case V6:
        case V7:
        case V8:
        case V9:
            count_len = 9;
            break;
        case V10:
        case V11:
        case V12:
        case V13:
        case V14:
        case V15:
        case V16:
        case V17:
        case V18:
        case V19:
        case V20:
        case V21:
        case V22:
        case V23:
        case V24:
        case V25:
        case V26:
            count_len = 11;
            break;
        case V27:
        case V28:
        case V29:
        case V30:
        case V31:
        case V32:
        case V33:
        case V34:
        case V35:
        case V36:
        case V37:
        case V38:
        case V39:
        case V40:
            count_len = 13;
            break;
        case MV2:
            count_len = 3;
            break;
        case MV3:
            count_len = 4;
            break;
        case MV4:
            count_len = 5;
            break;
        default:
            count_len = 13;
            break;
    }

    uint8_t byte;
    uint16_t tmp;

    byte = mode;
    byte <<= 4;
    byte ^= (len & ((0x1 << count_len) - 1)) >> (count_len - 4);

    data[data_loc++] = ((int)byte) & 0xFF;
    count_len -= 4;

    if (count_len >= 8) {
        byte = (len & ((0x1 << count_len) - 1) >> (count_len - 8)) & 0xFF;
        count_len -= 8;
        data[data_loc++] = ((int)byte) & 0xFF;
    }

    byte = len & ((0x1 << count_len) - 1);
    byte_loc = count_len;

    while (*message && count < len) {
        val1 = alphanumeric_lookup(*message);
        val2 = -1;
        if (count + 1 < len) {
            val2 = alphanumeric_lookup(*(message + 1));
        }

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
            count++;
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
            count += 2;
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
