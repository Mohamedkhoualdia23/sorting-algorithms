# Sorting Algorithms in C

## Student information

- **Student:** Mohamed Nour El Rahmen Khoualdia
- **University:** Université Badji Mokhtar – Annaba
- **Department:** Electronics
- **Module:** Algorithmique et Structures de Données
- **Instructor:** Dr. Sabri Ghazi
- **Work mode:** Individual (Solo)
- **Academic year:** 2026–2027

## Project overview

This project implements five required sorting algorithms in C: Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, and Quick Sort. It provides an interactive menu, correctness checks, execution-time and process-memory measurements, a 100,000-element test for Merge Sort and Quick Sort, multi-size comparisons, and CSV export.

Heap Sort is included as an optional bonus algorithm and is not included in the required five-algorithm comparison.

## Requirements and compiler

- Operating system used for the intended experiment: Windows 11.
- Language standard: ISO C11.
- Compiler: GCC (MinGW-w64 recommended on Windows).
- Compiler version: **Record the exact local version using `gcc --version` before final submission.**
- Windows measurement API: `QueryPerformanceCounter` for timing and `GetProcessMemoryInfo` from Windows PSAPI for process working-set memory.
- Standard C library: `stdio.h`, `stdlib.h`, `string.h`, `time.h`.

The student computer specifications supplied for this report:

| Component | Specification |
|---|---|
| CPU | AMD Ryzen 5 PRO 5675U with Radeon Graphics |
| Cores / logical processors | 6 / 12 |
| RAM | 16 GB DDR4, 2400 MT/s |
| GPU | AMD Radeon Graphics (integrated) |
| OS | Windows 11 |

## Repository structure

```text
sorting-algorithms/
├── README.md
├── Makefile
├── build_windows.bat
├── run_windows.bat
├── .gitignore
├── src/
│   ├── main.c
│   ├── sorting.c
│   ├── sorting.h
│   ├── benchmark.c
│   ├── benchmark.h
│   ├── utils.c
│   └── utils.h
├── tests/
│   └── test_sorting.c
├── results/
│   └── results.csv
└── scripts/
    └── plot_results.py
```

## Build and run on Windows 11

1. Install MinGW-w64 GCC and ensure `gcc` is available in PATH.
2. Open this folder in VS Code.
3. Open Terminal at the project root.
4. Build:

```powershell
gcc --version
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic src/main.c src/sorting.c src/benchmark.c src/utils.c -o sorting.exe -lpsapi
```

5. Run:

```powershell
.\sorting.exe
```

Alternatively, double-click `build_windows.bat`, then `run_windows.bat`.

## Menu

| Option | Action |
|---|---|
| 1–5 | Run one of the five required algorithms on a random array of a chosen size |
| 6 | Compare all five algorithms across several sizes and four input types; export `results/results.csv` |
| 7 | Run Merge Sort and Quick Sort on 100,000 random integers |
| 8 | Run a built-in correctness check |
| 0 | Exit |

Comparison sizes: 1,000; 5,000; 10,000; 50,000; 100,000. Bubble, Selection, and Insertion Sort are intentionally skipped above 10,000 elements because their quadratic running time can be excessive. The same generated input is copied for each algorithm within a comparison row. A fixed seed (`20261124`) makes input generation reproducible.

Input types: random, already sorted, reverse sorted, and duplicate-heavy.

## Algorithm descriptions and theoretical complexity

| Algorithm | Main idea | Best time | Average time | Worst time | Auxiliary space |
|---|---|---:|---:|---:|---:|
| Bubble Sort | Repeatedly swaps adjacent out-of-order values; stops early if a pass makes no swaps | O(n) | O(n²) | O(n²) | O(1) |
| Selection Sort | Repeatedly selects the minimum remaining value and places it next | O(n²) | O(n²) | O(n²) | O(1) |
| Insertion Sort | Inserts each next value into its correct position in the sorted prefix | O(n) | O(n²) | O(n²) | O(1) |
| Merge Sort | Divides the array, sorts both halves, and merges them | O(n log n) | O(n log n) | O(n log n) | O(n) |
| Quick Sort | Partitions around a median-of-three pivot and sorts the partitions | O(n log n) | O(n log n) | O(n²) | O(log n) typical call stack; smaller-side recursion bounds stack growth |

The implementation uses no built-in sorting function. Quick Sort recurses only into the smaller partition and iterates over the larger partition to limit call-stack growth. Merge Sort allocates a temporary array of `n` integers.

### Optional bonus: Heap Sort

Heap Sort builds a max heap and repeatedly moves its maximum element to the end. Its best, average, and worst time complexity are O(n log n), with O(1) auxiliary space. It is included as a bonus implementation and correctness test.

## Measurement methodology

- **Execution time:** measured around the sorting call using a high-resolution Windows performance counter (`QueryPerformanceCounter`).
- **Memory:** reports the change in process working-set size around the sort operation using Windows PSAPI (`GetProcessMemoryInfo`). This is an approximate process-level measurement, not an exact count of every allocation made by one function. Small or zero deltas can occur because of allocator and operating-system behavior.
- Each algorithm receives a fresh copy of the same source array.
- Correctness is checked by verifying that the resulting array is non-decreasing.
- The comparison CSV is generated by selecting menu option 6.

## Experimental results

Run option 6 on the target computer. The program writes measured rows to `results/results.csv`. Do not replace these values with invented or example measurements.

**Compiler version:** insert the exact output of `gcc --version`.

**Observed results:** complete this section after generating the CSV on the stated computer. Discuss the measured time for each algorithm and size, note any skipped quadratic runs, and compare the observed growth with the theoretical complexities above.

### Critical analysis guide

- Insertion Sort can perform well on small or already-sorted inputs because it has low overhead and an O(n) best case.
- Bubble Sort with early stopping can also finish quickly on already-sorted data, but its average and worst cases are quadratic.
- Selection Sort performs a quadratic number of comparisons even when the input is already sorted.
- Merge Sort provides predictable O(n log n) time but requires O(n) auxiliary memory.
- Quick Sort is often fast in practice and usually uses a small call stack, but its theoretical worst-case time is O(n²).
- Actual measurements can vary due to CPU load, compiler optimization, memory allocation, cache effects, and operating-system scheduling.

Write the actual observations from `results.csv` here after running the experiment. Do not claim a result that was not measured.

## Correctness tests

Compile and run the tests on Windows:

```powershell
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic tests/test_sorting.c src/sorting.c -o tests\test_sorting.exe
.\tests\test_sorting.exe
```

The test checks the five required algorithms and the optional Heap Sort against a known expected array.

## Submission checklist

- [ ] Run `gcc --version` and record the exact version above.
- [ ] Build the program without compiler errors.
- [ ] Run option 8 and confirm all correctness checks pass.
- [ ] Run option 6 and keep the generated `results/results.csv`.
- [ ] Run option 7 and record the 100,000-element results in the report.
- [ ] Add the actual experimental discussion based on the CSV.
- [ ] Create a **public** GitHub repository.
- [ ] Push source files, README, and result files.
- [ ] Make regular, meaningful commits during the work.
- [ ] Open the repository in a private/incognito browser window to verify public access.
- [ ] Submit the repository URL on the e-learning platform.

## GitHub commands

Run these from the project root after creating an empty public repository on GitHub:

```bash
git init
git add README.md .gitignore Makefile build_windows.bat run_windows.bat src tests results scripts
git commit -m "Add sorting algorithms and benchmark framework"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/sorting-algorithms.git
git push -u origin main
```

Replace the remote URL with the URL of your own GitHub repository.
