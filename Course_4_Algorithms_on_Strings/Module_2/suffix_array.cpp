/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 2 - Burrows-Wheeler Transform and Suffix Arrays
 * Assignment: Construct the Suffix Array of a String
 *
 * Logic:
 * For a string of length N <= 10,000, we can directly sort an array 
 * of suffix starting indices. To avoid the massive memory overhead 
 * of creating actual substring copies, we use a custom comparator 
 * that compares memory directly on the original text.
 *
 * Time Complexity: O(N^2 log N) worst-case, but practically much faster.
 * Space Complexity: O(N) to store the integer indices.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Build the suffix array by sorting indices
vector<int> BuildSuffixArray(const string& text) {
    int n = text.length();
    vector<int> suffix_array(n);
    
    // Initialize the array with starting indices 0 to n-1
    for (int i = 0; i < n; ++i) {
        suffix_array[i] = i;
    }

    // Sort indices based on the lexicographical order of the suffixes they represent
    sort(suffix_array.begin(), suffix_array.end(), [&text](int a, int b) {
        // string::compare is highly optimized and avoids substring memory allocation
        return text.compare(a, string::npos, text, b, string::npos) < 0;
    });

    return suffix_array;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (cin >> text) {
        vector<int> suffix_array = BuildSuffixArray(text);
        
        // Print the sorted indices separated by spaces
        for (int i = 0; i < suffix_array.size(); ++i) {
            cout << suffix_array[i] << (i == suffix_array.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
