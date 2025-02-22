#ifndef __REED_SOLOMON_H__
#define __REED_SOLOMON_H__

#include <stddef.h>

extern int gf_log[256];
extern int gf_exp[512];

void calculate_table(void);
int *generate_poly(size_t sz);
size_t reed_solomon(size_t data_sz, int data[data_sz], size_t ec_sz, int **error_correction);

#endif /* end of header guard: __REED_SOLOMON_H__ */
