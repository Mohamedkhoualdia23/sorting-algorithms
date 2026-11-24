#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "sorting.h"
#include <stddef.h>

typedef struct {
    double milliseconds;
    double memory_mb;
    int sorted_ok;
} BenchmarkResult;

double current_memory_mb(void);
BenchmarkResult benchmark_sort(SortFunction fn, const int *source, size_t n);

#endif
