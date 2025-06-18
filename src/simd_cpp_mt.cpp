#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <immintrin.h>
#include <cmath>

void compute_simd(const float* a, const float* b, float* c, size_t start, size_t end) {
    size_t i = start;
    for (; i + 7 < end; i += 8) {
        __m256 va = _mm256_loadu_ps(a + i);
        __m256 vb = _mm256_loadu_ps(b + i);
        __m256 vsum = _mm256_add_ps(va, vb);
        __m256 vsqrt = _mm256_sqrt_ps(vsum);
        _mm256_storeu_ps(c + i, vsqrt);
    }
    for (; i < end; ++i)
        c[i] = std::sqrt(a[i] + b[i]);
}

int main() {
    const size_t N = 10'000'000;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), c(N);
    int T = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(T);
    size_t block = N / T;

    auto start = std::chrono::high_resolution_clock::now();
    for (int t = 0; t < T; ++t) {
        size_t s = t * block;
        size_t e = (t == T - 1) ? N : s + block;
        threads[t] = std::thread(compute_simd, a.data(), b.data(), c.data(), s, e);
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> dur = end - start;
    std::cout << "SIMD (AVX2) MT," << dur.count() << std::endl;
}

