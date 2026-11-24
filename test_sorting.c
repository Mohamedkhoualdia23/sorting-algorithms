#include "../src/sorting.h"
#include <stdio.h>
#include <string.h>

typedef struct { const char *name; SortFunction fn; } TestAlgorithm;

int main(void) {
    const TestAlgorithm algorithms[] = {
        {"Bubble", bubble_sort}, {"Selection", selection_sort},
        {"Insertion", insertion_sort}, {"Merge", merge_sort},
        {"Quick", quick_sort}, {"Heap (bonus)", heap_sort}
    };
    const int input[] = {5, -1, 3, 3, 0, 100, -20, 5};
    const int expected[] = {-20, -1, 0, 3, 3, 5, 5, 100};
    int passed = 0;
    for (size_t i = 0; i < sizeof(algorithms)/sizeof(algorithms[0]); ++i) {
        int data[sizeof(input)/sizeof(input[0])];
        memcpy(data, input, sizeof(input));
        algorithms[i].fn(data, sizeof(data)/sizeof(data[0]));
        if (memcmp(data, expected, sizeof(expected)) == 0) {
            printf("[PASS] %s\n", algorithms[i].name);
            ++passed;
        } else {
            printf("[FAIL] %s\n", algorithms[i].name);
        }
    }
    printf("%d/%zu tests passed.\n", passed,
           sizeof(algorithms)/sizeof(algorithms[0]));
    return passed == sizeof(algorithms)/sizeof(algorithms[0]) ? 0 : 1;
}
