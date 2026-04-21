/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment: 2-1: Fibonacci Number
 *
 * Problem Description:
 * Compute the n-th Fibonacci number efficiently.
 * The Fibonacci sequence is defined as F(0) = 0, F(1) = 1, 
 * and F(i) = F(i-1) + F(i-2) for i >= 2.
 */

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

// The slow, naive recursive algorithm (used only for testing)
int fibonacci_naive(int n) {
    if (n <= 1)
        return n;

    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

// The fast, iterative algorithm for O(n) time complexity
int fibonacci_fast(int n) {
    if (n <= 1) {
        return n;
    }

    int previous = 0;
    int current = 1;

    for (int i = 2; i <= n; ++i) {
        int next_val = previous + current;
        previous = current;
        current = next_val;
    }

    return current;
}

void test_solution() {
    assert(fibonacci_fast(3) == 2);
    assert(fibonacci_fast(10) == 55);
    for (int n = 0; n < 20; ++n)
        assert(fibonacci_fast(n) == fibonacci_naive(n));
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 0;
    if (cin >> n) {
        // Output the result using the fast algorithm for the grader
        cout << fibonacci_fast(n) << '\n';
    }

    return 0;
}
