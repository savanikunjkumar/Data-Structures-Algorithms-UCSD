/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 3 - Algorithmic Challenges
 * Assignment: Find All Occurrences of a Pattern in a String
 *
 * Logic: Knuth-Morris-Pratt (KMP) Algorithm
 * To find all occurrences of a Pattern in a Genome in linear time O(|P| + |G|),
 * we concatenate them into a new string S = Pattern + "$" + Genome. We then 
 * compute the Prefix Array (pi array) for S. Any position where pi[i] == |Pattern| 
 * indicates a full match, and we extract the original starting index using math.
 *
 * Time Complexity: O(|Pattern| + |Genome|)
 * Space Complexity: O(|Pattern| + |Genome|) for the combined string and prefix array.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Computes the prefix function (pi array) for a given string
vector<int> ComputePrefixFunction(const string& P) {
    int m = P.length();
    vector<int> s(m, 0);
    int border = 0;
    
    for (int i = 1; i < m; ++i) {
        while (border > 0 && P[i] != P[border]) {
            border = s[border - 1]; // Fall back to the previous longest border
        }
        if (P[i] == P[border]) {
            border++;
        } else {
            border = 0;
        }
        s[i] = border;
    }
    return s;
}

// Finds all occurrences of pattern in text using KMP
vector<int> find_pattern(const string& pattern, const string& text) {
    vector<int> result;
    
    // Edge case checks
    if (pattern.empty() || text.empty() || pattern.length() > text.length()) {
        return result;
    }

    // Combine strings with a unique delimiter
    string S = pattern + "$" + text;
    vector<int> s = ComputePrefixFunction(S);
    int p_len = pattern.length();

    // Scan the prefix array for matches
    // We only need to start checking after the 'Pattern + $' part
    for (int i = p_len + 1; i < S.length(); ++i) {
        if (s[i] == p_len) {
            // i is the end of the match in string S.
            // Math to map it back to the starting index of the original text:
            result.push_back(i - 2 * p_len);
        }
    }
    
    return result;
}

int main() {
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string pattern, text;
    if (cin >> pattern >> text) {
        vector<int> result = find_pattern(pattern, text);
        
        // Output formatting
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << (i + 1 == result.size() ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
