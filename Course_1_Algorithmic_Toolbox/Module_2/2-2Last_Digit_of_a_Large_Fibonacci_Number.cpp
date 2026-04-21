/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: 2-2: Last Digit of a Large Fibonacci Number
 *
 * Problem Description:
 * Find the last digit of the n-th Fibonacci number.
 * To prevent integer overflow, we only compute and store 
 * the last digit of each Fibonacci number in the sequence.
 */

#include <iostream>

using namespace std;

int get_fibonacci_last_digit_fast(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 2; i <= n; ++i) {
        // Compute only the last digit of the next Fibonacci number
        int next_val = (previous + current) % 10;
        previous = current;
        current = next_val;
    }

    return current;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        // Output the result using the fast algorithm
        cout << get_fibonacci_last_digit_fast(n) << '\n';
    }

    return 0;
}
