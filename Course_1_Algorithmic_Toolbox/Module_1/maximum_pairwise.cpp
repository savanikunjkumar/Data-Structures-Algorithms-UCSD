/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 1
 * Assignment: Maximum Pairwise Product
 *
 * Problem Description:
 * Find the maximum product of two distinct numbers in a sequence of non-negative integers.
 * Input: An integer n and a sequence of n non-negative integers.
 * Output: The maximum value that can be obtained by multiplying two different elements from the sequence.
 * Constraints: 2 <= n <= 2 * 10^5; 0 <= a_i <= 2 * 10^5.
 */

#include <iostream>
#include <vector>

using namespace std;

// Function returns a long long to prevent integer overflow 
// when multiplying two numbers up to 200,000
long long MaxPairwiseProductFast(const vector<int>& numbers) {
    int n = numbers.size();

    // Find the index of the absolute largest number
    int max_index1 = -1;
    for (int i = 0; i < n; ++i) {
        if (max_index1 == -1 || numbers[i] > numbers[max_index1]) {
            max_index1 = i;
        }
    }

    // Find the index of the second largest number (must be a different index)
    int max_index2 = -1;
    for (int j = 0; j < n; ++j) {
        if ((j != max_index1) && ((max_index2 == -1) || (numbers[j] > numbers[max_index2]))) {
            max_index2 = j;
        }
    }

    // Cast the values to long long before multiplication
    return (long long)(numbers[max_index1]) * numbers[max_index2];
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> numbers(n);
        for (int i = 0; i < n; ++i) {
            cin >> numbers[i];
        }

        cout << MaxPairwiseProductFast(numbers) << "\n";
    }

    return 0;
}
