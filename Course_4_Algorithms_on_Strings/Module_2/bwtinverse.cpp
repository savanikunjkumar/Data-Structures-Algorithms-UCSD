/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 2 - Burrows-Wheeler Transform
 * Assignment: Reconstruct a String from its BWT
 *
 * Logic: First-Last Property
 * We compute the starting positions of each character in the First column 
 * by counting their frequencies in the Last column (BWT). We then build 
 * an L_to_F (Last to First) mapping. By following this mapping starting 
 * from the '$' character, we can reconstruct the original text backwards 
 * in pure O(N) time.
 *
 * Time Complexity: O(N) where N is the length of the Transform.
 * Space Complexity: O(N) for the L_to_F mapping array and reconstructed string.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Helper to map characters to integer indices for fast array lookups
int char_to_idx(char c) {
    switch(c) {
        case '$': return 0;
        case 'A': return 1;
        case 'C': return 2;
        case 'G': return 3;
        case 'T': return 4;
        default: return -1;
    }
}

string InverseBWT(const string& bwt) {
    int n = bwt.length();
    if (n == 0) return "";

    // Step 1: Count the frequencies of each character in the BWT string
    int count[5] = {0};
    for (int i = 0; i < n; ++i) {
        count[char_to_idx(bwt[i])]++;
    }

    // Step 2: Determine the starting index of each character in the 'First' column
    int start[5] = {0};
    for (int i = 1; i < 5; ++i) {
        start[i] = start[i - 1] + count[i - 1];
    }

    // Step 3: Build the Last-to-First (L_to_F) mapping
    vector<int> l_to_f(n);
    int current_count[5] = {0}; // Tracks the i-th occurrence of a character
    for (int i = 0; i < n; ++i) {
        int c_idx = char_to_idx(bwt[i]);
        l_to_f[i] = start[c_idx] + current_count[c_idx];
        current_count[c_idx]++;
    }

    // Step 4: Reconstruct the string backwards
    string text(n, ' ');
    text[n - 1] = '$'; // We know the string always ends with '$'
    
    // The row where the First column has '$' is guaranteed to be row 0 
    // because '$' is lexicographically the smallest character.
    int curr = 0; 
    
    for (int i = n - 2; i >= 0; --i) {
        text[i] = bwt[curr]; // The character preceding First[curr] is Last[curr] (which is bwt[curr])
        curr = l_to_f[curr]; // Jump to that character's position in the First column
    }

    return text;
}

int main() {
    // Fast I/O is crucial for processing the 1,000,000 length string within 2 seconds
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string bwt;
    if (cin >> bwt) {
        cout << InverseBWT(bwt) << "\n";
    }
    
    return 0;
}
