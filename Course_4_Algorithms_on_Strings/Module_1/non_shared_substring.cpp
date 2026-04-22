/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 1 - Suffix Trees
 * Assignment: Find the Shortest Non-Shared Substring of Two Strings
 *
 * Logic: BFS with State Machine
 * Building a full suffix tree is complex. Since |Text| <= 2000, we can build a 
 * fast transition table (state machine) for Text2. Then, we run a Breadth-First 
 * Search (BFS) starting from all possible positions in Text1. The first path 
 * that fails to transition in the Text2 state machine is our shortest non-shared 
 * substring.
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Helper to convert nucleotide to an index 0-3
int charToIndex(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    if (c == 'T') return 3;
    return -1;
}

string solve(string p, string q) {
    int n = p.length();
    int m = q.length();

    // next_pos[i][c] stores the earliest occurrence of character 'c' 
    // in string 'q' at or after index 'i'.
    vector<vector<int>> next_pos(m + 1, vector<int>(4, -1));

    // Precompute transitions for Text2 (q)
    for (int j = 0; j < 4; ++j) {
        int last_seen = -1;
        for (int i = m - 1; i >= 0; --i) {
            if (charToIndex(q[i]) == j) {
                last_seen = i;
            }
            next_pos[i][j] = last_seen;
        }
    }

    // BFS Queue stores: {current_index_in_p, current_index_in_q, length_of_substring}
    struct State {
        int p_idx;
        int q_idx;
        int len;
    };

    queue<State> Q;
    
    // We want the shortest overall, so we must try starting from every position in Text1
    for (int i = 0; i < n; ++i) {
        Q.push({i, 0, 1}); 
    }

    int min_len = 1e9;
    int best_start = -1;

    while (!Q.empty()) {
        State curr = Q.front();
        Q.pop();

        // If we found a shorter one earlier, we don't need to process longer ones
        if (curr.len > min_len) continue;

        if (curr.p_idx >= n) continue;

        int c_idx = charToIndex(p[curr.p_idx]);

        // Try to transition in Text2
        int next_q = next_pos[curr.q_idx][c_idx];

        if (next_q == -1) {
            // We fell off the Text2 state machine! 
            // This means we found a substring in p that isn't in q.
            if (curr.len < min_len) {
                min_len = curr.len;
                best_start = curr.p_idx - curr.len + 1;
            }
        } else {
            // Transition is valid, push the next state to explore longer substrings
            Q.push({curr.p_idx + 1, next_q + 1, curr.len + 1});
        }
    }

    return p.substr(best_start, min_len);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string p, q;
    if (!(cin >> p >> q)) return 0;

    cout << solve(p, q) << "\n";

    return 0;
}
