import math, time, threading

N = 10_000_000
a = [1.0] * N
b = [2.0] * N
c = [0.0] * N
T = 8  # lub os.cpu_count()

def worker(start, end):
    for i in range(start, end):
        c[i] = math.sin(a[i]) * math.cos(b[i]) + math.sqrt(a[i] + b[i])

threads = []
block = N // T

start = time.time()
for t in range(T):
    s = t * block
    e = N if t == T - 1 else s + block
    thread = threading.Thread(target=worker, args=(s, e))
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()
end = time.time()

print(f"Czysty Python MT,{(end - start)*1000:.2f}")

