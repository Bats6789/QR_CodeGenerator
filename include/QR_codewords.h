#ifndef __QR_CODEWORDS_H__
#define __QR_CODEWORDS_H__

#include <stddef.h>

size_t generate_codewords(const char *message, int **codewords);
size_t pad_data(int **codewords, size_t data_sz, size_t desired_sz);

#endif /* end of header guard: __QR_CODEWORDS_H__ */
