/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 2 - Burrows-Wheeler Transform
 * Assignment: Matching Against a Compressed String (BetterBWMatching)
 *
 * Logic:
 * We precompute the 'FirstOccurrence' of each character and a 'Count' tally 
 * matrix. This allows us to update the 'top' and 'bottom' pointers in O(1) 
 * time for each character in the pattern, completely avoiding the need to 
 * scan the BWT string repeatedly.
 *
 * Time Complexity: O(|BWT| + Sum of |Patterns|) 
 * Space Complexity: O(|BWT| * |Alphabet|)
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Map nucleotides to fixed integer indices (0 to 4) for our arrays
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

// Precompute the FirstOccurrence array and the Count matrix
void PreprocessBWT(const string& bwt, vector<int>& starts, vector<vector<int>>& count_occ) {
    int n = bwt.length();
    
    // Step 1: Get the total frequency of each character
    vector<int> freq(5, 0);
    for (int i = 0; i < n; i++) {
        freq[char_to_idx(bwt[i])]++;
    }
    
    // Step 2: Compute FirstOccurrence ('starts' array)
    starts[0] = 0; // '$' is always at index 0
    for (int i = 1; i < 5; i++) {
        starts[i] = starts[i - 1] + freq[i - 1];
    }
    
    // Step 3: Compute the Count tally matrix
    // count_occ[i][char] stores occurrences of 'char' up to index i-1 in BWT
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            count_occ[i + 1][j] = count_occ[i][j];
        }
        count_occ[i + 1][char_to_idx(bwt[i])]++;
    }
}

// Count matches of a single pattern using the precomputed structures
int CountOccurrences(const string& pattern, const string& bwt, const vector<int>& starts, const vector<vector<int>>& count_occ) {
    int top = 0;
    int bottom = bwt.length() - 1;
    int p_idx = pattern.length() - 1; // Start from the last letter of the pattern
    
    while (top <= bottom) {
        if (p_idx >= 0) {
            char symbol = pattern[p_idx];
            p_idx--;
            int c_idx = char_to_idx(symbol);
            
            // Check if the symbol actually appears in the current top-bottom range
            // count_occ[bottom + 1] - count_occ[top] gives the exact count in range
            if (count_occ[bottom + 1][c_idx] > count_occ[top][c_idx]) {
                top = starts[c_idx] + count_occ[top][c_idx];
                bottom = starts[c_idx] + count_occ[bottom + 1][c_idx] - 1;
            } else {
                return 0; // Symbol doesn't exist in the valid range, pattern fails
            }
        } else {
            // Pattern exhausted successfully, return the size of the matched block
            return bottom - top + 1;
        }
    }
    return 0;
}

int main() {
    // Fast I/O is critical for the large precomputation constraints
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string bwt;
    if (!(cin >> bwt)) return 0;

    int n;
    cin >> n;

    vector<string> patterns(n);
    for (int i = 0; i < n; i++) {
        cin >> patterns[i];
    }

    // Pre-allocate memory for our structures
    // 'starts' holds 5 elements, 'count_occ' holds (N + 1) * 5 elements
    vector<int> starts(5, 0);
    vector<vector<int>> count_occ(bwt.length() + 1, vector<int>(5, 0));
    
    PreprocessBWT(bwt, starts, count_occ);

    // Process each pattern
    for (int i = 0; i < n; i++) {
        cout << CountOccurrences(patterns[i], bwt, starts, count_occ);
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << "\n";

    return 0;
}
