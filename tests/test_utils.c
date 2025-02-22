#include "test_utils.h"

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
