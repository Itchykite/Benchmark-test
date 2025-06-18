import subprocess
import pandas as pd
from collections import defaultdict
import os

NUM_RUNS = 10
OUT_DIR = "out"
RESULTS_FILE = os.path.join(OUT_DIR, "results.csv")
RESULTS_AVG_FILE = os.path.join(OUT_DIR, "results_avg.csv")

aggregated = defaultdict(list)

for i in range(NUM_RUNS):
    print(f"🔁 Uruchamiam test {i + 1}/{NUM_RUNS}...")
    subprocess.run(["bash", "run_all.sh"], check=True)

    df = pd.read_csv(RESULTS_FILE)
    for _, row in df.iterrows():
        name = row["version"].strip()
        time = float(row["time_ms"])
        aggregated[name].append(time)

# Wylicz średnią i zapisz
avg_results = {
    "version": [],
    "avg_time_ms": []
}

for version, times in aggregated.items():
    avg = sum(times) / len(times)
    avg_results["version"].append(version)
    avg_results["avg_time_ms"].append(avg)

df_avg = pd.DataFrame(avg_results)
df_avg.to_csv(RESULTS_AVG_FILE, index=False)
print(f"✅ Zapisano uśrednione wyniki do {RESULTS_AVG_FILE}")

