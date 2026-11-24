#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef enum {
    DATA_RANDOM = 1,
    DATA_SORTED,
    DATA_REVERSE,
    DATA_DUPLICATES
} DataType;

void fill_array(int *a, size_t n, DataType type, unsigned int seed);
const char *data_type_name(DataType type);
void print_array(const int *a, size_t n);

#endif
