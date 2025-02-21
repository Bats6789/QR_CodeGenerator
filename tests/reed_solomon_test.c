#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        for (size_t j = 1; j < 11; ++j) {
            buf[i + j] ^= gf_exp[gf_log[gp[j]] + gf_log[coef]];
        }
    }

    memcpy(ec, buf + data_sz, sizeof *ec * ec_sz);
    *error_correction = ec;

	free(buf);
	free(gp);

    return ec_sz;
}

void fprint_array(FILE *stream, size_t sz, int array[sz]) {
	for (size_t i = 0; i < sz; ++i) {
		fprintf(stream, "%d%c", array[i], i + 1 == sz ? '\0' : ' ');
	}
}

bool array_equal(int *array1, int *array2, size_t sz) {
	for (size_t i = 0; i < sz; ++i) {
		if (array1[i] != array2[i]) {
			return false;
		}
	}
	return true;
}

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
