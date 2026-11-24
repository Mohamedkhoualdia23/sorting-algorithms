#include "sorting.h"
#include "benchmark.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *name;
    SortFunction function;
} Algorithm;

static const Algorithm algorithms[] = {
    {"Bubble Sort", bubble_sort},
    {"Selection Sort", selection_sort},
    {"Insertion Sort", insertion_sort},
    {"Merge Sort", merge_sort},
    {"Quick Sort", quick_sort}
};
#define ALGORITHM_COUNT (sizeof(algorithms) / sizeof(algorithms[0]))

static int read_int(const char *prompt, int min_value, int max_value) {
    char line[128], *end;
    long value;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof(line), stdin)) return min_value;
        value = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') ++end;
        if (end != line && *end == '\0' && value >= min_value && value <= max_value)
            return (int)value;
        printf("Invalid input. Enter a number from %d to %d.\n", min_value, max_value);
    }
}

static size_t read_size(void) {
    char line[128], *end;
    unsigned long long value;
    for (;;) {
        printf("Array size (1..1000000): ");
        if (!fgets(line, sizeof(line), stdin)) return 10;
        value = strtoull(line, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') ++end;
        if (end != line && *end == '\0' && value >= 1 && value <= 1000000)
            return (size_t)value;
        puts("Invalid size.");
    }
}

static void run_one(void) {
    int choice = read_int("Algorithm (1 Bubble, 2 Selection, 3 Insertion, 4 Merge, 5 Quick): ", 1, 5);
    size_t n = read_size();
    int *data = (int *)malloc(n * sizeof(int));
    if (!data) { puts("Memory allocation failed."); return; }
    fill_array(data, n, DATA_RANDOM, 20261124u);
    BenchmarkResult r = benchmark_sort(algorithms[choice - 1].function, data, n);
    printf("\n%s | n=%zu | time=%.3f ms | process-memory delta=%.3f MB | sorted=%s\n",
           algorithms[choice - 1].name, n, r.milliseconds, r.memory_mb,
           r.sorted_ok ? "YES" : "NO");
    free(data);
}

static void run_big_array(void) {
    const size_t n = 100000;
    int *data = (int *)malloc(n * sizeof(int));
    if (!data) { puts("Memory allocation failed."); return; }
    fill_array(data, n, DATA_RANDOM, 20261124u);
    puts("\nBig array: 100,000 random integers (fixed seed).");
    const size_t chosen[] = {3, 4}; /* Merge and Quick */
    for (size_t k = 0; k < 2; ++k) {
        BenchmarkResult r = benchmark_sort(algorithms[chosen[k]].function, data, n);
        printf("%-14s time=%10.3f ms | memory delta=%8.3f MB | sorted=%s\n",
               algorithms[chosen[k]].name, r.milliseconds, r.memory_mb,
               r.sorted_ok ? "YES" : "NO");
    }
    free(data);
}

static int append_csv(const char *path, const char *algorithm, size_t n,
                      const char *type, BenchmarkResult r) {
    FILE *f = fopen(path, "a");
    if (!f) return 0;
    fprintf(f, "%s,%zu,%s,%.6f,%.6f,%s\n", algorithm, n, type,
            r.milliseconds, r.memory_mb, r.sorted_ok ? "PASS" : "FAIL");
    fclose(f);
    return 1;
}

static void comparison_mode(void) {
    const size_t sizes[] = {1000, 5000, 10000, 50000, 100000};
    const DataType types[] = {DATA_RANDOM, DATA_SORTED, DATA_REVERSE, DATA_DUPLICATES};
    const size_t size_count = sizeof(sizes) / sizeof(sizes[0]);
    const size_t type_count = sizeof(types) / sizeof(types[0]);
    const char *csv_path = "results/results.csv";
    FILE *f = fopen(csv_path, "w");
    if (!f) {
        puts("Could not create results/results.csv. Run the program from the project root.");
        return;
    }
    fputs("algorithm,array_size,input_type,time_ms,memory_delta_mb,correctness\n", f);
    fclose(f);

    puts("\nComparison mode. Quadratic algorithms are limited to 10,000 elements.");
    puts("All algorithms receive identical data for each size and input type.");
    printf("%-16s %10s %-12s %12s %14s %s\n",
           "Algorithm", "N", "Input", "Time(ms)", "MemDelta(MB)", "Check");

    for (size_t t = 0; t < type_count; ++t) {
        for (size_t s = 0; s < size_count; ++s) {
            size_t n = sizes[s];
            int *base = (int *)malloc(n * sizeof(int));
            if (!base) { puts("Allocation failed; comparison stopped."); return; }
            fill_array(base, n, types[t], 20261124u);
            for (size_t a = 0; a < ALGORITHM_COUNT; ++a) {
                if (a < 3 && n > 10000) continue;
                BenchmarkResult r = benchmark_sort(algorithms[a].function, base, n);
                printf("%-16s %10zu %-12s %12.3f %14.3f %s\n",
                       algorithms[a].name, n, data_type_name(types[t]),
                       r.milliseconds, r.memory_mb, r.sorted_ok ? "PASS" : "FAIL");
                append_csv(csv_path, algorithms[a].name, n, data_type_name(types[t]), r);
            }
            free(base);
        }
    }
    printf("\nCSV exported to %s\n", csv_path);
}

static void print_menu(void) {
    puts("\n========== SORTING ALGORITHMS ==========");
    puts("1. Bubble Sort");
    puts("2. Selection Sort");
    puts("3. Insertion Sort");
    puts("4. Merge Sort");
    puts("5. Quick Sort");
    puts("6. Compare all five algorithms (CSV + four input types)");
    puts("7. Big array test (100,000; Merge + Quick)");
    puts("8. Run correctness tests built into the program");
    puts("0. Exit");
}

int main(void) {
    for (;;) {
        print_menu();
        int choice = read_int("Your choice: ", 0, 8);
        if (choice == 0) { puts("Goodbye."); break; }
        if (choice >= 1 && choice <= 5) run_one();
        else if (choice == 6) comparison_mode();
        else if (choice == 7) run_big_array();
        else if (choice == 8) {
            int sample[] = {9, -2, 4, 4, 0, 17, -8, 1};
            int copy[sizeof(sample) / sizeof(sample[0])];
            int ok = 1;
            for (size_t a = 0; a < ALGORITHM_COUNT; ++a) {
                memcpy(copy, sample, sizeof(sample));
                algorithms[a].function(copy, sizeof(copy) / sizeof(copy[0]));
                if (!is_sorted(copy, sizeof(copy) / sizeof(copy[0]))) ok = 0;
            }
            puts(ok ? "Built-in correctness check: PASS" : "Built-in correctness check: FAIL");
        }
    }
    return 0;
}
