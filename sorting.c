#include "sorting.h"
#include <stdlib.h>

static void swap_int(int *x, int *y) {
    int t = *x; *x = *y; *y = t;
}

void bubble_sort(int *a, size_t n) {
    if (!a || n < 2) return;
    for (size_t end = n; end > 1; --end) {
        int changed = 0;
        for (size_t j = 1; j < end; ++j) {
            if (a[j - 1] > a[j]) {
                swap_int(&a[j - 1], &a[j]);
                changed = 1;
            }
        }
        if (!changed) break;
    }
}

void selection_sort(int *a, size_t n) {
    if (!a || n < 2) return;
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; ++j)
            if (a[j] < a[min_index]) min_index = j;
        if (min_index != i) swap_int(&a[i], &a[min_index]);
    }
}

void insertion_sort(int *a, size_t n) {
    if (!a || n < 2) return;
    for (size_t i = 1; i < n; ++i) {
        int key = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > key) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = key;
    }
}

static void merge_ranges(int *a, int *tmp, size_t left, size_t mid, size_t right) {
    size_t i = left, j = mid, k = left;
    while (i < mid && j < right)
        tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
    while (i < mid) tmp[k++] = a[i++];
    while (j < right) tmp[k++] = a[j++];
    for (k = left; k < right; ++k) a[k] = tmp[k];
}

static void merge_recursive(int *a, int *tmp, size_t left, size_t right) {
    if (right - left < 2) return;
    size_t mid = left + (right - left) / 2;
    merge_recursive(a, tmp, left, mid);
    merge_recursive(a, tmp, mid, right);
    merge_ranges(a, tmp, left, mid, right);
}

void merge_sort(int *a, size_t n) {
    if (!a || n < 2) return;
    int *tmp = (int *)malloc(n * sizeof(int));
    if (!tmp) return;
    merge_recursive(a, tmp, 0, n);
    free(tmp);
}

static int median_of_three(int x, int y, int z) {
    if (x < y) {
        if (y < z) return y;
        return (x < z) ? z : x;
    }
    if (x < z) return x;
    return (y < z) ? z : y;
}

/* Recurse only on the smaller partition; loop over the larger one.
   This bounds call-stack depth to O(log n), even for poor partitions. */
static void quick_recursive(int *a, long long low, long long high) {
    while (low < high) {
        long long mid = low + (high - low) / 2;
        int pivot = median_of_three(a[low], a[mid], a[high]);
        long long i = low, j = high;
        while (i <= j) {
            while (a[i] < pivot) ++i;
            while (a[j] > pivot) --j;
            if (i <= j) {
                swap_int(&a[i], &a[j]);
                ++i; --j;
            }
        }
        if (j - low < high - i) {
            if (low < j) quick_recursive(a, low, j);
            low = i;
        } else {
            if (i < high) quick_recursive(a, i, high);
            high = j;
        }
    }
}

void quick_sort(int *a, size_t n) {
    if (!a || n < 2) return;
    quick_recursive(a, 0, (long long)n - 1);
}

static void sift_down(int *a, size_t root, size_t count) {
    for (;;) {
        size_t child = root * 2 + 1;
        if (child >= count) return;
        if (child + 1 < count && a[child] < a[child + 1]) ++child;
        if (a[root] >= a[child]) return;
        swap_int(&a[root], &a[child]);
        root = child;
    }
}

void heap_sort(int *a, size_t n) {
    if (!a || n < 2) return;
    for (size_t start = n / 2; start > 0; --start)
        sift_down(a, start - 1, n);
    for (size_t end = n; end > 1; --end) {
        swap_int(&a[0], &a[end - 1]);
        sift_down(a, 0, end - 1);
    }
}

int is_sorted(const int *a, size_t n) {
    if (!a && n != 0) return 0;
    for (size_t i = 1; i < n; ++i)
        if (a[i - 1] > a[i]) return 0;
    return 1;
}
