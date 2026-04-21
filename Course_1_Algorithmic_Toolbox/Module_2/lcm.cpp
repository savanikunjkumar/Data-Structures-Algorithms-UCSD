/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: Least Common Multiple
 *
 * Problem Description:
 * Find the least common multiple of two integers a and b.
 * The fast approach computes the LCM using the formula: 
 * LCM(a, b) = (a * b) / GCD(a, b). This drastically reduces 
 * the time complexity compared to linear iteration.
 */

#include <iostream>

using namespace std;

// Helper function to find the GCD using the highly efficient Euclidean algorithm
long long gcd_fast(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd_fast(b, a % b);
}

// Fast algorithm to find the LCM
long long lcm_fast(long long a, long long b) {
    // Divide first to prevent potential integer overflow during multiplication
    return (a / gcd_fast(a, b)) * b;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    if (cin >> a >> b) {
        // Output the result using the fast algorithm
        cout << lcm_fast(a, b) << '\n';
    }

    return 0;
}
