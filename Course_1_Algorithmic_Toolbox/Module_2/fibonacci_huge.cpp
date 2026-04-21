/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 2
 * Assignment:Fibonacci Number Again
 *
 * Problem Description:
 * Find the n-th Fibonacci number modulo m, where n can be extremely large.
 * The fast approach utilizes the Pisano Period—the mathematical property 
 * that the sequence of Fibonacci numbers modulo m is periodic.
 */

#include <iostream>

using namespace std;

// Helper function to calculate the length of the Pisano Period for a given m
long long get_pisano_period(long long m) {
    long long previous = 0;
    long long current = 1;
    
    // The period length is guaranteed to be <= m * m
    for (long long i = 0; i < m * m; ++i) {
        long long temp = (previous + current) % m;
        previous = current;
        current = temp;
        
        // A Pisano Period always starts with 0 and 1
        if (previous == 0 && current == 1) {
            return i + 1;
        }
    }
    return 0;
}

// Fast algorithm using the Pisano Period
long long get_fibonacci_huge_fast(long long n, long long m) {
    // Find the repeating cycle length
    long long pisano_period = get_pisano_period(m);
    
    // Shrink the massive n down to its equivalent position within the period
    n = n % pisano_period;
    
    if (n <= 1) {
        return n;
    }
        
    long long previous = 0;
    long long current = 1;
    
    for (long long i = 2; i <= n; ++i) {
        long long temp = (previous + current) % m;
        previous = current;
        current = temp;
    }
    
    return current % m;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, m;
    if (cin >> n >> m) {
        // Output the result using the fast algorithm
        cout << get_fibonacci_huge_fast(n, m) << '\n';
    }
    
    return 0;
}
