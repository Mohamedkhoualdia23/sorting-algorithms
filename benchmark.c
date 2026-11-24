#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>
static double now_ms(void) {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1000.0 / (double)frequency.QuadPart;
}
double current_memory_mb(void) {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
        return (double)pmc.WorkingSetSize / (1024.0 * 1024.0);
    return -1.0;
}
#else
#include <sys/resource.h>
static double now_ms(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}
double current_memory_mb(void) {
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
#if defined(__APPLE__)
        return (double)usage.ru_maxrss / (1024.0 * 1024.0);
#else
        return (double)usage.ru_maxrss / 1024.0;
#endif
    }
    return -1.0;
}
#endif

BenchmarkResult benchmark_sort(SortFunction fn, const int *source, size_t n) {
    BenchmarkResult result = {0.0, -1.0, 0};
    if (!fn || (!source && n)) return result;

    int *work = NULL;
    if (n) {
        work = (int *)malloc(n * sizeof(int));
        if (!work) return result;
        memcpy(work, source, n * sizeof(int));
    }

    double mem_before = current_memory_mb();
    double start = now_ms();
    fn(work, n);
    double end = now_ms();
    double mem_after = current_memory_mb();

    result.milliseconds = end - start;
    result.memory_mb = (mem_before >= 0.0 && mem_after >= 0.0)
        ? (mem_after > mem_before ? mem_after - mem_before : 0.0) : -1.0;
    result.sorted_ok = is_sorted(work, n);

    free(work);
    return result;
}
