#include <iostream>
#include <stdint.h>
#include <gtest/gtest.h>

uint32_t binomialCoeff(uint32_t n, uint32_t k) {
    // Calculate the binomial coefficient
    if (k > n - k) {
        k = n - k;
    }
    uint32_t res = 1;
    for (uint32_t i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int main() {
    // Test cases
    std::cout << binomialCoeff(5, 2) << std::endl;  // Expected output: 10
    std::cout << binomialCoeff(10, 3) << std::endl; // Expected output: 120
    std::cout << binomialCoeff(6, 4) << std::endl;  // Expected output: 15
    std::cout << binomialCoeff(8, 0) << std::endl;  // Expected output: 1
    std::cout << binomialCoeff(0, 0) << std::endl;  // Expected output: 1

    return 0;
}