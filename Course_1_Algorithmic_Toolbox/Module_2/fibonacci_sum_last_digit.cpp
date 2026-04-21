/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: Last Digit of the Sum of Fibonacci Numbers
 *
 * Problem Description:
 * Find the last digit of the sum of the first n Fibonacci numbers.
 * Utilizing the mathematical property Sum(F_0...F_n) = F_{n+2} - 1
 * and the Pisano period of modulo 10 (which is exactly 60), the 
 * computation time is drastically reduced to O(1).
 */

#include <iostream>

using namespace std;

// Fast algorithm using mathematical properties of Fibonacci sums
long long fibonacci_sum_fast(long long n) {
    if (n <= 1) {
        return n;
    }

    // The sum of first n Fibonacci numbers is F_{n+2} - 1.
    // The Pisano period for modulo 10 is exactly 60.
    // So we only need to find the (n + 2) % 60 th Fibonacci number.
    long long new_n = (n + 2) % 60;
    
    // If new_n becomes 0, F_0 is 0. 0 - 1 in modulo 10 arithmetic is 9.
    if (new_n == 0) {
        return 9;
    }

    long long previous = 0;
    long long current = 1;

    for (int i = 2; i <= new_n; ++i) {
        long long temp = (previous + current) % 10;
        previous = current;
        current = temp;
    }

    // We subtract 1 from the (n+2)th Fibonacci number.
    // If current is 0, subtracting 1 gives -1. To handle negative numbers 
    // cleanly in modulo 10, we add 9 (which is mathematically identical to 
    // subtracting 1 and adding 10).
    return (current + 9) % 10;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (cin >> n) {
        // Output the result using the O(1) fast algorithm
        cout << fibonacci_sum_fast(n) << '\n';
    }

    return 0;
}
