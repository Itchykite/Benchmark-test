#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

int main() {
    const size_t N = 10'000'000;
    std::vector<float> a(N, 1.0f), b(N, 2.0f), c(N);

    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i)
        c[i] = std::sin(a[i]) * std::cos(b[i]) + std::sqrt(a[i] + b[i]);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> dur = end - start;
    std::cout << "Czysty C++," << dur.count() << std::endl;
}

