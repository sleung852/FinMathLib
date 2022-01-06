#ifndef D9454A5C_8EEC_4C92_BF72_8805ADD00651
#define D9454A5C_8EEC_4C92_BF72_8805ADD00651

#include <map>
#include <chrono>
#include <iostream>

// 3.9.3
int fibonacciNumber(int n) {
    // cout << "Executed!" << endl;
    if (n==0) return 1;
    if (n==1) return 1;
    return fibonacciNumber(n-1) + fibonacciNumber(n-2);
}

// 18.12.1
void computeFibonacciNumberFast(int n, std::map<int, int>& cache) {
    cache[n] = cache[n-1] + cache[n-2];
}

int fibonacciNumberFast(int n) {
    std::map<int, int> cache;
    cache[0] = 1;
    cache[1] = 1;
    for (int i=2; i<=n; i++) {
        computeFibonacciNumberFast(i, cache);
    }
    return cache[n];
}

void testFibonacciNumberSpeed() {
    int x = 20;
    int result;

    std::cout << "Fibonacci Number Generation Speed Test" << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    result = fibonacciNumber(x);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Duration (Slow): " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    begin = std::chrono::steady_clock::now();
    result = fibonacciNumberFast(x);
    end = std::chrono::steady_clock::now();
    std::cout << "Duration (Fast): " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

#endif /* D9454A5C_8EEC_4C92_BF72_8805ADD00651 */
