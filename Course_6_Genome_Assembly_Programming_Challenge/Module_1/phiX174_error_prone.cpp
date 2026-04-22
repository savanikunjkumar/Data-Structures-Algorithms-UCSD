/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 1 - The 2011 European E. coli Outbreak
 * Assignment: phi X174 Genome Assembly (Error-Prone Reads)
 *
 * Logic: Overlap Graph with Error Tolerance
 * We find overlaps by counting mismatches. A greedy Hamiltonian path 
 * approach is used to link reads. Given high coverage and low error rates, 
 * picking the "best" overlap (max length, min errors) is a robust strategy.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Returns the length of the best overlap found between a suffix of s1 and prefix of s2
// Returns a pair: {overlap_length, mismatch_count}
pair<int, int> get_overlap_with_errors(const string& s1, const string& s2, int min_overlap = 30) {
    int n = s1.length();
    int best_len = 0;
    int best_mismatches = 1000;

    // Check overlaps from length 99 down to min_overlap
    for (int len = n - 1; len >= min_overlap; --len) {
        int mismatches = 0;
        for (int i = 0; i < len; ++i) {
            if (s1[n - len + i] != s2[i]) {
                mismatches++;
            }
        }
        
        // 5% error threshold (mismatches / len <= 0.05)
        if (mismatches <= len * 0.05) {
            return {len, mismatches};
        }
    }
    return {0, 1000};
}

string assemble_circular_genome(vector<string>& reads) {
    int n = reads.size();
    vector<bool> visited(n, false);
    
    int curr = 0;
    visited[curr] = true;
    string genome = reads[curr];
    
    vector<int> path = {0};

    for (int i = 1; i < n; ++i) {
        int best_next = -1;
        int max_overlap = -1;
        int min_mismatches = 1000;

        for (int j = 0; j < n; ++j) {
            if (visited[j]) continue;

            auto res = get_overlap_with_errors(reads[curr], reads[j]);
            if (res.first > max_overlap) {
                max_overlap = res.first;
                min_mismatches = res.second;
                best_next = j;
            } else if (res.first == max_overlap && res.second < min_mismatches) {
                min_mismatches = res.second;
                best_next = j;
            }
        }

        if (best_next != -1) {
            genome += reads[best_next].substr(max_overlap);
            visited[best_next] = true;
            curr = best_next;
            path.push_back(best_next);
        }
    }

    // Circular trim: overlap between last and first read
    auto circular = get_overlap_with_errors(reads[curr], reads[path[0]]);
    if (circular.first > 0) {
        genome = genome.substr(0, genome.length() - circular.first);
    }

    return genome;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string r;
    while (cin >> r) {
        // Basic cleanup: remove duplicates to reduce search space
        if (find(reads.begin(), reads.end(), r) == reads.end()) {
            reads.push_back(r);
        }
    }

    if (reads.empty()) return 0;

    cout << assemble_circular_genome(reads) << endl;

    return 0;
}
