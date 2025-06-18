import numpy as np
import time
from concurrent.futures import ThreadPoolExecutor

N = 10_000_000
a = np.full(N, 1.0, dtype=np.float32)
b = np.full(N, 2.0, dtype=np.float32)
c = np.empty(N, dtype=np.float32)
T = 8  # lub os.cpu_count()
block = N // T

def worker(i):
    start = i * block
    end = N if i == T - 1 else start + block
    c[start:end] = np.sin(a[start:end]) * np.cos(b[start:end]) + np.sqrt(a[start:end] + b[start:end])

start = time.time()
with ThreadPoolExecutor(max_workers=T) as executor:
    executor.map(worker, range(T))
end = time.time()

print(f"Numpy Python MT,{(end - start)*1000:.2f}")

