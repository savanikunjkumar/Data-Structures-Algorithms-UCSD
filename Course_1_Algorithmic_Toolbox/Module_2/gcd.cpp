/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: Greatest Common Divisor
 *
 * Problem Description:
 * Find the greatest common divisor of two non-negative integers a and b.
 * The Euclidean algorithm is used to compute the GCD in logarithmic time,
 * completely avoiding the slow linear iteration of the naive approach.
 */

#include <iostream>

using namespace std;

// Fast algorithm using the Euclidean method
int gcd_fast(int a, int b) {
    // Base case: if the remainder is 0, the other number is the GCD
    if (b == 0) {
        return a;
    }
    // Recursive call: GCD(a, b) is the same as GCD(b, a % b)
    return gcd_fast(b, a % b);
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    if (cin >> a >> b) {
        // Output the result using the fast Euclidean algorithm
        cout << gcd_fast(a, b) << '\n';
    }

    return 0;
}
