#ifndef ADVENT_OF_CODE_MATH_H
#define ADVENT_OF_CODE_MATH_H

#include <bits/stdc++.h>

uint64_t ModExp(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;

    // Reduce the base modulo modulus
    base = base % modulus;
    while (exponent > 0)
    {
        // If the exponent is odd, multiply the result with the base
        if (exponent & 1)
            result = (result * base) % modulus;

        // Square the base and reduce the exponent by half
        base     = (base * base) % modulus;
        exponent = exponent >> 1;
    }
    return result;
}

#endif//ADVENT_OF_CODE_MATH_H
