#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

void compute(const float* a, const float* b, float* c, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i)
        c[i] = std::sin(a[i]) * std::cos(b[i]) + std::sqrt(a[i] + b[i]);
}

int main() {
    const size_t N = 10'000'000;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), c(N);

    const int T = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(T);
    size_t block = N / T;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < T; ++i) {
        size_t s = i * block;
        size_t e = (i == T - 1) ? N : s + block;
        threads[i] = std::thread(compute, a.data(), b.data(), c.data(), s, e);
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> dur = end - start;
    std::cout << "Czysty C++ MT," << dur.count() << std::endl;
}

