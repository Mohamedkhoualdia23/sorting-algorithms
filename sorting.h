#ifndef SORTING_H
#define SORTING_H

#include <stddef.h>

typedef void (*SortFunction)(int *, size_t);

void bubble_sort(int *a, size_t n);
void selection_sort(int *a, size_t n);
void insertion_sort(int *a, size_t n);
void merge_sort(int *a, size_t n);
void quick_sort(int *a, size_t n);
void heap_sort(int *a, size_t n); /* Optional bonus */

int is_sorted(const int *a, size_t n);

#endif
