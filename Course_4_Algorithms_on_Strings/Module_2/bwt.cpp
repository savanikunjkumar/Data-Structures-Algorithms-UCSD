/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 2 - Burrows-Wheeler Transform and Suffix Arrays
 * Assignment: Construct the Burrows-Wheeler Transform of a String
 *
 * Logic:
 * We avoid explicitly building the N x N matrix of cyclic rotations to save memory. 
 * Instead, we create a vector of starting indices [0 ... N-1] and sort them using 
 * a custom lambda function that compares the cyclic strings on the fly. Finally, 
 * the last character of the sorted rotation starting at index 'i' is exactly the 
 * character at '(i + N - 1) % N'.
 *
 * Time Complexity: O(N^2 log N) - Valid and extremely fast for N <= 1000.
 * Space Complexity: O(N) - Only stores an array of indices.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string BWT(const string& text) {
    int n = text.length();
    
    // Store the starting indices of the cyclic rotations
    vector<int> rotations(n);
    for (int i = 0; i < n; ++i) {
        rotations[i] = i;
    }

    // Custom comparator to sort the implicit cyclic rotations
    auto compare_rotations = [&text, n](int i, int j) {
        for (int k = 0; k < n; ++k) {
            char a = text[(i + k) % n];
            char b = text[(j + k) % n];
            if (a != b) {
                return a < b; // Sort lexicographically
            }
        }
        return false; // Strings are perfectly equal
    };

    // Sort the indices based on the cyclic strings they represent
    sort(rotations.begin(), rotations.end(), compare_rotations);

    // Build the BWT (last column of the sorted matrix)
    string result = "";
    result.reserve(n); // Pre-allocate memory to avoid reallocation overhead
    for (int i = 0; i < n; ++i) {
        // The last character of the rotation starting at 'rotations[i]'
        result += text[(rotations[i] + n - 1) % n];
    }

    return result;
}

int main() {
    // Fast I/O optimization to beat the 0.5s C++ time limit
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (cin >> text) {
        cout << BWT(text) << "\n";
    }

    return 0;
}
