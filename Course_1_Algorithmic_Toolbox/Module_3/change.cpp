/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Money Change
 *
 * Problem Description:
 * Find the minimum number of coins needed to change the input value 
 * (an integer) into coins with denominations 1, 5, and 10.
 * A greedy approach is used by taking as many of the largest 
 * denominations as possible using integer division and modulo.
 */

#include <iostream>

using namespace std;

// Fast O(1) algorithm using math instead of loops
int get_change(int m) {
    int total_coins = 0;

    // Take as many 10s as possible
    total_coins += m / 10;
    m = m % 10;

    // Take as many 5s as possible from the remainder
    total_coins += m / 5;
    m = m % 5;

    // The rest will be 1s
    total_coins += m;

    return total_coins;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    if (cin >> m) {
        // Output the minimum number of coins
        cout << get_change(m) << '\n';
    }
    
    return 0;
}
