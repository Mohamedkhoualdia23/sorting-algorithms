#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

static unsigned int next_random(unsigned int *state) {
    *state = (*state * 1664525u) + 1013904223u;
    return *state;
}

void fill_array(int *a, size_t n, DataType type, unsigned int seed) {
    if (!a) return;
    unsigned int state = seed ? seed : 1u;
    for (size_t i = 0; i < n; ++i) {
        switch (type) {
            case DATA_SORTED: a[i] = (int)i; break;
            case DATA_REVERSE: a[i] = (int)(n - i); break;
            case DATA_DUPLICATES: a[i] = (int)(next_random(&state) % 21u) - 10; break;
            case DATA_RANDOM:
            default: a[i] = (int)(next_random(&state) % 200001u) - 100000; break;
        }
    }
}

const char *data_type_name(DataType type) {
    switch (type) {
        case DATA_RANDOM: return "random";
        case DATA_SORTED: return "sorted";
        case DATA_REVERSE: return "reverse";
        case DATA_DUPLICATES: return "duplicates";
        default: return "unknown";
    }
}

void print_array(const int *a, size_t n) {
    for (size_t i = 0; i < n; ++i)
        printf("%d%s", a[i], (i + 1 == n) ? "\n" : " ");
}
