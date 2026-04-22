/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 1 - The 2011 European E. coli Outbreak
 * Assignment: Assembling the phi X174 Genome from Error-Prone Reads
 *
 * Logic: Greedy Hamiltonian Path with Hamming Distance
 * We use an overlap function that allows for a 5% mismatch rate. 
 * By picking the best possible overlap at each step, we reconstruct 
 * the circular genome while ignoring the individual sequencing errors.
 *
 * Time Complexity: O(N^2 * L) where N=1618, L=100.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to store the result of an overlap check
struct OverlapResult {
    int length;
    int mismatches;

    bool is_better_than(const OverlapResult& other) const {
        if (length != other.length) return length > other.length;
        return mismatches < other.mismatches;
    }
};

// Computes the best overlap satisfying the 5% error threshold
OverlapResult get_overlap(const string& a, const string& b, int min_overlap = 15) {
    int n = a.length();
    // Try overlaps from 99 down to min_overlap
    for (int len = n - 1; len >= min_overlap; --len) {
        int mismatches = 0;
        for (int i = 0; i < len; ++i) {
            if (a[n - len + i] != b[i]) {
                mismatches++;
            }
        }
        // Check if mismatches are within 5% of overlap length
        if (mismatches <= len * 0.05) {
            return {len, mismatches};
        }
    }
    return {0, 1000};
}

string assemble(vector<string>& reads) {
    int n = reads.size();
    vector<bool> visited(n, false);
    vector<int> path;
    
    int curr = 0;
    visited[curr] = true;
    path.push_back(curr);
    string genome = reads[curr];

    for (int i = 1; i < n; ++i) {
        OverlapResult best_overlap = {-1, 1000};
        int next_read = -1;

        for (int j = 0; j < n; ++j) {
            if (visited[j]) continue;

            OverlapResult res = get_overlap(reads[curr], reads[j]);
            if (res.length > 0 && res.is_better_than(best_overlap)) {
                best_overlap = res;
                next_read = j;
            }
        }

        if (next_read != -1) {
            genome += reads[next_read].substr(best_overlap.length);
            visited[next_read] = true;
            curr = next_read;
            path.push_back(next_read);
        }
    }

    // Circularity: Overlap the last read with the first read
    OverlapResult circular = get_overlap(reads[curr], reads[path[0]]);
    if (circular.length > 0) {
        genome = genome.substr(0, genome.length() - circular.length);
    }

    return genome;
}

int main() {
    // Fast I/O is standard practice for VIT/GATE level coding
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string r;
    while (cin >> r) {
        // Only keep unique reads to speed up the O(N^2) process
        if (find(reads.begin(), reads.end(), r) == reads.end()) {
            reads.push_back(r);
        }
    }

    if (reads.empty()) return 0;

    cout << assemble(reads) << endl;

    return 0;
}
