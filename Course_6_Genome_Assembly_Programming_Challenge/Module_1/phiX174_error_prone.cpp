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
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Problem: Assembling phi X174 Genome from Error-Prone Reads
 * Optimization: K-mer indexing to reduce overlap search space.
 * Tolerance: 5% error rate in overlaps as per instructions.
 */

struct OverlapResult {
    int length;
    int mismatches;
};

// Fuzzy overlap check: returns length and mismatch count if under 5% threshold
OverlapResult get_fuzzy_overlap(const string& s1, const string& s2, int min_overlap = 30) {
    int n = s1.length();
    // Check from longest possible overlap down to min_overlap
    for (int len = n - 1; len >= min_overlap; --len) {
        int mismatches = 0;
        int threshold = len * 0.05; // 5% error threshold
        
        bool possible = true;
        for (int i = 0; i < len; ++i) {
            if (s1[n - len + i] != s2[i]) {
                mismatches++;
                if (mismatches > threshold) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (possible) return {len, mismatches};
    }
    return {0, 1000};
}

string assemble_error_prone(vector<string>& reads) {
    int n = reads.size();
    vector<bool> used(n, false);
    
    // Step 1: K-mer Indexing
    // We map a 15-char prefix to read indices.
    // Even with 1% error, the chance of the first 15 chars being error-free is high.
    unordered_map<string, vector<int>> kmer_map;
    for (int i = 0; i < n; ++i) {
        kmer_map[reads[i].substr(0, 15)].push_back(i);
        // Also index a slightly shifted k-mer to account for an error at the very start
        kmer_map[reads[i].substr(1, 15)].push_back(i);
    }

    int curr = 0;
    used[curr] = true;
    string genome = reads[curr];
    vector<int> path = {0};

    for (int count = 1; count < n; ++count) {
        int best_next = -1;
        int max_overlap = -1;
        int min_mismatches = 1000;

        string suffix_zone = reads[curr].substr(reads[curr].length() - 95);
        
        // Step 2: Instead of checking all N reads, only check those sharing a k-mer
        // We scan the suffix of the current read for any 15-mer present in our map
        for (int pos = 0; pos < 70; ++pos) {
            string target_kmer = suffix_zone.substr(pos, 15);
            if (kmer_map.count(target_kmer)) {
                for (int neighbor_idx : kmer_map[target_kmer]) {
                    if (used[neighbor_idx]) continue;

                    auto res = get_fuzzy_overlap(reads[curr], reads[neighbor_idx]);
                    if (res.length > max_overlap) {
                        max_overlap = res.length;
                        min_mismatches = res.mismatches;
                        best_next = neighbor_idx;
                    } else if (res.length == max_overlap && res.mismatches < min_mismatches) {
                        min_mismatches = res.mismatches;
                        best_next = neighbor_idx;
                    }
                }
            }
            // If we found a very strong overlap, we can break early to save time
            if (max_overlap > 85 && min_mismatches <= 1) break;
        }

        if (best_next != -1) {
            genome += reads[best_next].substr(max_overlap);
            used[best_next] = true;
            curr = best_next;
            path.push_back(best_next);
        }
    }

    // Circular trim
    auto circular = get_fuzzy_overlap(reads[curr], reads[path[0]]);
    if (circular.length > 0) {
        genome = genome.substr(0, genome.length() - circular.length);
    }

    return genome;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string r;
    while (cin >> r) {
        reads.push_back(r);
    }

    if (reads.empty()) return 0;
    cout << assemble_error_prone(reads) << endl;

    return 0;
}
