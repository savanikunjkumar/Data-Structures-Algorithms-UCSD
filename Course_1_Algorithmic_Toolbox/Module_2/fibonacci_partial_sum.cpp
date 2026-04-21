/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: Last Digit of a Partial Sum of Fibonacci Numbers
 *
 * Problem Description:
 * Find the last digit of the sum of Fibonacci numbers from m to n.
 * Utilizes the mathematical property Sum(F_m...F_n) = F_{n+2} - F_{m+1}
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

// Fast algorithm for the partial sum
long long get_fibonacci_partial_sum_fast(long long from, long long to) {
    // We need F_{to+2} - F_{from+1}
    int last_digit_to = get_fibonacci_last_digit(to + 2);
    int last_digit_from = get_fibonacci_last_digit(from + 1);

    
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long from, to;
    if (cin >> from >> to) {
        cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
    }

    return 0;
}
