#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include <stdbool.h>
#include <stdio.h>

void fprint_array(FILE *stream, size_t sz, int array[sz]);
bool array_equal(int *array1, int *array2, size_t sz);

#endif /* end of header guard: __TEST_UTILS_H__ */
