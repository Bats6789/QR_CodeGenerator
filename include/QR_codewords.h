#ifndef __QR_CODEWORDS_H__
#define __QR_CODEWORDS_H__

#include "QRcode.h"
#include <stddef.h>

size_t generate_codewords(const char *message, int **codewords, QR_version_t version, QR_recovery_t recovery);
size_t generate_codewords_byte(const char *message, size_t len, int **codewords, QR_version_t version);
size_t generate_codewords_alpha(const char *message, size_t len, int **codewords, QR_version_t version);
size_t generate_codewords_num(const char *message, size_t len, int **codewords, QR_version_t version);
size_t pad_data(int **codewords, size_t data_sz, size_t desired_sz);

#endif /* end of header guard: __QR_CODEWORDS_H__ */
