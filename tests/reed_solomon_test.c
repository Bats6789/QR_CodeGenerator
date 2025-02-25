#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reed_solomon.h"
#include "test_utils.h"

bool run_test(size_t data_sz, int data[data_sz], size_t expected_sz, int expected[expected_sz]) {
	int *ec;
	size_t ec_sz;

    ec_sz = reed_solomon(data_sz, data, expected_sz, &ec);

    if (ec_sz != expected_sz) {
        fputs("Incorrect amount of values\n", stderr);
        fputs("Expected: ", stderr);
        fprint_array(stderr, ec_sz, expected);
        fputc('\n', stderr);
        fputs("Actual: ", stderr);
        fprint_array(stderr, ec_sz, ec);
        fputc('\n', stderr);
        return false;
    }

    if (!array_equal(expected, ec, ec_sz)) {
        fputs("Incorrect values\n", stderr);
        fputs("Expected: ", stderr);
        fprint_array(stderr, expected_sz, expected);
        fputc('\n', stderr);
        fputs("Actual: ", stderr);
        fprint_array(stderr, ec_sz, ec);
        fputc('\n', stderr);
        return false;
    }

    free(ec);

	return true;
}


int main(int argc, char **argv) {
    int data[] = {16, 32, 12, 86, 97, 128, 236, 17, 236, 17, 236, 17, 236, 17, 236, 17};
    int data2[] = {39,  5,   39,  161, 52,  158, 132, 210, 122, 18,  11,  196, 88, 231, 40,  102, 116, 160, 142, 81,
                   18,  11,  196, 88,  231, 40,  102, 84,  206, 148, 17,  202, 34, 68,  88,  231, 40,  102, 84,  206,
                   148, 17,  202, 34,  65,  128, 185, 34,  165, 196, 183, 145, 49, 110, 23,  69,  201, 21,  46,  37,
                   188, 137, 139, 112, 186, 46,  72,  169, 113, 45,  228, 76,  91, 133, 209, 114, 69,  75};
    int expected[] = {165, 36, 212, 193, 237, 54, 199, 135, 44, 85};
    int expected2[] = {153, 137, 240, 232, 20, 11, 61, 137, 138, 172, 179, 251, 210, 249, 247, 194, 62, 99, 200, 33};
    calculate_table();

	// basic reed_solomon test
	if (!run_test(sizeof data / sizeof *data, data, sizeof expected / sizeof *expected, expected)) {
		return EXIT_FAILURE;
	}

	// Divide by zero bug
	if (!run_test(sizeof data2 / sizeof *data2, data2, sizeof expected2 / sizeof *expected2, expected2)) {
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}
