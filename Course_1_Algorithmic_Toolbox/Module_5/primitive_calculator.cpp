/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 5
 * Assignment: Primitive Calculator
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> optimal_sequence(int n) {
    vector<int> sequence;
    // min_ops[i] stores the minimum number of operations to reach number i
    vector<int> min_ops(n + 1);

    for (int i = 2; i <= n; i++) {
        // Start with the +1 case
        min_ops[i] = min_ops[i - 1] + 1;
        
        // Check if divide by 2 is better
        if (i % 2 == 0) {
            min_ops[i] = min(min_ops[i], min_ops[i / 2] + 1);
        }
        
        // Check if divide by 3 is better
        if (i % 3 == 0) {
            min_ops[i] = min(min_ops[i], min_ops[i / 3] + 1);
        }
    }

    // Backtrack to find the actual sequence
    int current = n;
    while (current >= 1) {
        sequence.push_back(current);
        if (current == 1) break;

        // Determine which path we took to get to 'current'
        if (min_ops[current] == min_ops[current - 1] + 1) {
            current = current - 1;
        } else if (current % 2 == 0 && min_ops[current] == min_ops[current / 2] + 1) {
            current = current / 2;
        } else if (current % 3 == 0 && min_ops[current] == min_ops[current / 3] + 1) {
            current = current / 3;
        }
    }

    // The sequence is backtracked, so reverse it to get 1 -> n
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int main() {
    // Fast I/O for grading limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> sequence = optimal_sequence(n);
        
        // The problem asks for the number of operations (sequence size - 1)
        cout << sequence.size() - 1 << "\n";
        for (size_t i = 0; i < sequence.size(); ++i) {
            cout << sequence[i] << (i == sequence.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
