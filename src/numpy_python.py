import numpy as np
import time

N = 10_000_000
a = np.full(N, 1.0, dtype=np.float32)
b = np.full(N, 2.0, dtype=np.float32)

start = time.time()
c = np.sin(a) * np.cos(b) + np.sqrt(a + b)
end = time.time()

print(f"Numpy Python,{(end - start)*1000:.2f}")

