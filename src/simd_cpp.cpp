#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h>
#include <cmath>

int main() {
    const size_t N = 10'000'000;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), c(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i + 8 <= N; i += 8) {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vsum = _mm256_add_ps(va, vb);
        __m256 vsqrt = _mm256_sqrt_ps(vsum);
        _mm256_storeu_ps(&c[i], vsqrt);
    }
    for (size_t i = (N / 8) * 8; i < N; ++i)
        c[i] = std::sqrt(a[i] + b[i]);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    std::cout << "SIMD C++," << dur.count() << std::endl;
}

