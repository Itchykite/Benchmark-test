import math, time

N = 10_000_000
a = [1.0] * N
b = [2.0] * N
c = [0.0] * N

start = time.time()
for i in range(N):
    c[i] = math.sin(a[i]) * math.cos(b[i]) + math.sqrt(a[i] + b[i])
end = time.time()

print(f"Czysty Python,{(end - start)*1000:.2f}")

