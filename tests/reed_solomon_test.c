#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reed_solomon.h"
#include "test_utils.h"

int main(int argc, char **argv) {
    int *ec;
    size_t ec_sz;
    int data[] = {16, 32, 12, 86, 97, 128, 236, 17, 236, 17, 236, 17, 236, 17, 236, 17};
    int expected[] = {165, 36, 212, 193, 237, 54, 199, 135, 44, 85};
    calculate_table();
    ec_sz = reed_solomon(16, data, 10, &ec);

    if (ec_sz != 10) {
        fputs("Incorrect amount of values\n", stderr);
        fputs("Expected: ", stderr);
        fprint_array(stderr, sizeof expected / sizeof *expected, expected);
        fputc('\n', stderr);
        fputs("Actual: ", stderr);
        fprint_array(stderr, ec_sz, ec);
        fputc('\n', stderr);
        return EXIT_FAILURE;
    }

    if (!array_equal(expected, ec, ec_sz)) {
        fputs("Incorrect values\n", stderr);
        fputs("Expected: ", stderr);
        fprint_array(stderr, sizeof expected / sizeof *expected, expected);
        fputc('\n', stderr);
        fputs("Actual: ", stderr);
        fprint_array(stderr, ec_sz, ec);
        fputc('\n', stderr);
        return EXIT_FAILURE;
    }

    free(ec);

    return EXIT_SUCCESS;
}
