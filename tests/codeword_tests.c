#include <stdbool.h>
#include <stdio.h>

#include "QR_codewords.h"
#include "codeword_lookup.h"
#include "test_utils.h"

struct check_t {
    char symbol;
    int expected;
    int actual;
    bool passed;
};

int main(int argc, char **argv) {
    // alphanumeric
    struct check_t alnum_check[45];
    bool all_passed = true;
    int *codewords;
    size_t sz;
    int expected[] = {0x20, 0x3D, 0x27, 0xA1, 0x20, 0xBC, 0x30, 0x11, 0xEC, 0x11,
                      0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11, 0xEC, 0x11, 0xEC};

    // 0-9
    for (size_t i = 0; i < 10; ++i) {
        alnum_check[i] = (struct check_t){'0' + i, i, -1, false};
    }
    // A-Z
    for (size_t i = 0; i < 26; ++i) {
        alnum_check[i + 10] = (struct check_t){'A' + i, 10 + i, -1, false};
    }
    // Special characters
    alnum_check[36] = (struct check_t){' ', 36, -1, false};
    alnum_check[37] = (struct check_t){'$', 37, -1, false};
    alnum_check[38] = (struct check_t){'%', 38, -1, false};
    alnum_check[39] = (struct check_t){'*', 39, -1, false};
    alnum_check[40] = (struct check_t){'+', 40, -1, false};
    alnum_check[41] = (struct check_t){'-', 41, -1, false};
    alnum_check[42] = (struct check_t){'.', 42, -1, false};
    alnum_check[43] = (struct check_t){'/', 44, -1, false};
    alnum_check[44] = (struct check_t){':', 44, -1, false};

    for (size_t i = 0; i < 45; ++i) {
        alnum_check[i].actual = alphanumeric_lookup(alnum_check[i].symbol);
        alnum_check[i].passed = alnum_check[i].expected == alnum_check[i].actual;
        if (!alnum_check[i].passed) {
            all_passed = false;
        }
    }

    if (!all_passed) {
        fputs("The following values failed:\n", stderr);
        for (size_t i = 0; i < 45; ++i) {
            if (!alnum_check[i].passed) {
                fprintf(stderr, "\t%c:\n\t\texpected (%d)\n\t\tactual (%d)\n", alnum_check[i].symbol,
                        alnum_check[i].expected, alnum_check[i].actual);
            }
        }
    }

    sz = generate_codewords("TEST123", &codewords);

    if (sz != 19 || array_equal(expected, codewords, sz)) {
        fputs("Incorrect values\n", stderr);
        fputs("Expected: ", stderr);
        fprint_array(stderr, sizeof expected / sizeof *expected, expected);
        fputc('\n', stderr);
        fputs("Actual: ", stderr);
        fprint_array(stderr, sz, codewords);
        fputc('\n', stderr);
    }

    return 0;
}
