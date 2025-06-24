#include <immintrin.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>
#include <omp.h>

int main()
{
    const int N = 10'000'000;
    std::vector<float> a(N), b(N), c(N);

    #pragma omp parallel
    {
        std::mt19937 rng(123 + omp_get_thread_num()); 
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        #pragma omp for
        for (size_t i = 0; i < N; ++i)
        {
            a[i] = dist(rng);
            b[i] = dist(rng);
        }
    }

    for (size_t i = 0; i + 8 <= N; i += 8)
    {
        __m256 va = _mm256_loadu_ps(&a[i]);
        __m256 vb = _mm256_loadu_ps(&b[i]);
        __m256 vsum = _mm256_add_ps(va, vb);
        __m256 vsqrt = _mm256_sqrt_ps(vsum);
        _mm256_storeu_ps(&c[i], vsqrt);
    }

    for (size_t i = (N / 8) * 8; i < N; ++i)
        c[i] = std::sqrt(a[i] + b[i]);


    std::ofstream out("result.txt");
    if (!out) 
    {
        std::cerr << "Damn that's too bad!\n";
        return 1;
    }

    for (size_t i = 0; i < N; ++i)
        out << i << ": " << c[i] << '\n';

    out.close(); 

    return 0;
}
