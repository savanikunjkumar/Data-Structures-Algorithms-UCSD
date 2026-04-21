/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: Last Digit of the Sum of Squares of Fibonacci Numbers
 *
 * Problem Description:
 * Find the last digit of the sum of the squares of the first n Fibonacci numbers.
 * Utilizes the geometric property that Sum(F_i^2) from 0 to n equals F_n * F_{n+1},
 * combined with the Pisano period of 60 for modulo 10.
 */

#include <iostream>

using namespace std;

// Helper function to get the last digit of the n-th Fibonacci number
int get_fibonacci_last_digit(long long n) {
    // The Pisano period for modulo 10 is 60
    n = n % 60;
    
    if (n <= 1) {
        return n;
    }

    int previous = 0;
    int current = 1;

    for (int i = 2; i <= n; ++i) {
        int temp = (previous + current) % 10;
        previous = current;
        current = temp;
    }

    return current;
}

// Fast algorithm using the area formula F_n * F_{n+1}
long long fibonacci_sum_squares_fast(long long n) {
    // Get the last digit of F_n and F_{n+1}
    int last_digit_current = get_fibonacci_last_digit(n);
    int last_digit_next = get_fibonacci_last_digit(n + 1);

    // Multiply them and take modulo 10 to get the final last digit
    return (last_digit_current * last_digit_next) % 10;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n;
    if (cin >> n) {
        cout << fibonacci_sum_squares_fast(n) << '\n';
    }

    return 0;
}
