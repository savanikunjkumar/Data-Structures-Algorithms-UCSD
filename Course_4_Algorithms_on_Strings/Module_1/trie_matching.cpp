/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 1 - Suffix Trees
 * Assignment: Multiple Pattern Matching
 *
 * Logic:
 * We build a Trie from the collection of patterns. Then, for every possible 
 * starting position 'i' in the Text, we thread the substring starting at 'i' 
 * through the Trie. If we successfully reach a leaf node, it means a pattern 
 * matched completely, and we record 'i'.
 *
 * Time Complexity: O(|Text| * max(|Patterns|))
 * Space Complexity: O(Sum of |Patterns|)
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Structure to represent a node in the Trie
struct Node {
    map<char, int> next;
    
    // If a node has no outgoing edges, it's the end of a pattern
    bool isLeaf() const {
        return next.empty();
    }
};

vector<int> solve(const string& text, const vector<string>& patterns) {
    vector<int> result;
    if (patterns.empty() || text.empty()) return result;

    // Step 1: Build the Trie
    vector<Node> trie(1); // Initialize with the root node at index 0
    for (const string& pattern : patterns) {
        int current = 0;
        for (char c : pattern) {
            // If the edge doesn't exist, create it and a new node
            if (trie[current].next.find(c) == trie[current].next.end()) {
                trie[current].next[c] = trie.size();
                trie.emplace_back(); // Add a new empty node
            }
            // Move to the next node
            current = trie[current].next[c];
        }
    }

    // Step 2: Match patterns in the Text
    int n = text.length();
    for (int i = 0; i < n; i++) {
        int current = 0;
        int j = i; // Pointer for the text
        
        while (true) {
            // If we hit a leaf, we matched a full pattern
            if (trie[current].isLeaf()) {
                result.push_back(i);
                break;
            }
            // If we run out of text before hitting a leaf, no match
            if (j >= n) {
                break;
            }
            
            char c = text[j];
            // If there's a valid edge for the current character, follow it
            if (trie[current].next.find(c) != trie[current].next.end()) {
                current = trie[current].next[c];
                j++;
            } else {
                // Mismatch found, stop checking this starting index 'i'
                break; 
            }
        }
    }

    return result;
}

int main() {
    // Fast I/O is critical to pass the strict 1-second C++ time limit
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

    // Print results separated by spaces
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
