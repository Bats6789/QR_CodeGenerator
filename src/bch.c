#include <math.h>
#include <stddef.h>

#include "bch.h"

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

uint32_t golay(uint32_t data) {
    uint32_t res = 0;
    size_t bit_len = floor(log2(data)) + 1;
    uint32_t poly = 0b1111100100101;

    res = data << (12 - bit_len);

    for (size_t i = 0; i < bit_len; ++i) {
        if ((res & 0x800) == 0x800) {
            res <<= 1;
            res ^= poly;
        } else {
            res <<= 1;
        }
        res &= 0xFFF;
    }

    return res;
}
