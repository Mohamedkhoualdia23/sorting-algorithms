"""Optional chart generator. Install matplotlib with: python -m pip install matplotlib"""
import csv
from collections import defaultdict
from pathlib import Path
import matplotlib.pyplot as plt

csv_path = Path("results/results.csv")
if not csv_path.exists():
    raise SystemExit("Run menu option 6 first to create results/results.csv")

groups = defaultdict(list)
with csv_path.open(newline="", encoding="utf-8") as f:
    for row in csv.DictReader(f):
        if row["correctness"] == "PASS":
            groups[(row["input_type"], row["algorithm"])].append(
                (int(row["array_size"]), float(row["time_ms"]))
            )

for input_type in sorted({key[0] for key in groups}):
    plt.figure()
    for (kind, algorithm), points in groups.items():
        if kind != input_type:
            continue
        points.sort()
        plt.plot([p[0] for p in points], [p[1] for p in points], marker="o", label=algorithm)
    plt.xlabel("Array size (elements)")
    plt.ylabel("Execution time (ms)")
    plt.title(f"Sorting performance - {input_type} input")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"results/{input_type}_time.png", dpi=160)
    plt.close()

print("Charts saved in results/.")
