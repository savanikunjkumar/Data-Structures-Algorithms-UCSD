/*
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 1 - Suffix Trees
 * Assignment: Generalized Multiple Pattern Matching
 *
 * Logic:
 * We use an optimized Trie array structure. To handle prefix overlaps 
 * (e.g., patterns "A" and "AT"), we use a 'patternEnd' flag instead of 
 * relying on leaf nodes. The moment we hit a flagged node during traversal, 
 * we log the index and break to avoid duplicate outputs.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Helper to convert nucleotides to fixed array indices for O(1) lookups
int letterToIndex(char c) {
    switch(c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
        default: return -1;
    }
}

// Optimized Node structure
struct Node {
    int next[4];
    bool patternEnd;
    
    Node() {
        fill(next, next + 4, -1);
        patternEnd = false;
    }
};

vector<int> solve(const string& text, const vector<string>& patterns) {
    vector<int> result;
    if (patterns.empty() || text.empty()) return result;

    // Step 1: Build the Trie
    vector<Node> trie(1); 
    for (const string& pattern : patterns) {
        int current = 0;
        for (char c : pattern) {
            int idx = letterToIndex(c);
            if (trie[current].next[idx] == -1) {
                trie[current].next[idx] = trie.size();
                trie.emplace_back();
            }
            current = trie[current].next[idx];
        }
        // Explicitly mark that a pattern finishes at this node
        trie[current].patternEnd = true; 
    }

    // Step 2: Match patterns in the Text
    int n = text.length();
    for (int i = 0; i < n; i++) {
        int current = 0;
        int j = i; 
        
        while (true) {
            // If the current node marks the end of ANY pattern, it's a match
            if (trie[current].patternEnd) {
                result.push_back(i);
                break; // Stop checking this 'i' to prevent duplicate outputs
            }
            
            // If we run out of text before a match
            if (j >= n) {
                break;
            }
            
            int idx = letterToIndex(text[j]);
            // If there's a valid edge, follow it
            if (trie[current].next[idx] != -1) {
                current = trie[current].next[idx];
                j++;
            } else {
                // Mismatch found, move to the next starting index in the text
                break; 
            }
        }
    }

    return result;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (!(cin >> text)) return 0;

    int n;
    cin >> n;

    vector<string> patterns(n);
    for (int i = 0; i < n; i++) {
        cin >> patterns[i];
    }

    vector<int> ans = solve(text, patterns);

    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i];
        if (i + 1 < (int)ans.size()) {
            cout << " ";
        } else {
            cout << "\n";
        }
    }

    return 0;
}
