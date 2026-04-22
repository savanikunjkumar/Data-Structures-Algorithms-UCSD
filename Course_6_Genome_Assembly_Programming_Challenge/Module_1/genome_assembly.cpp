/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 1 - The 2011 European E. coli Outbreak
 * Assignment: Assembling the phi X174 Genome
 *
 * Logic: Greedy Hamiltonian Path on an Overlap Graph
 * We start with an arbitrary read and repeatedly find the next unvisited 
 * read with the maximum overlap. This greedy approach works efficiently 
 * for error-free reads to reconstruct the circular genome.
 *
 * Time Complexity: O(N^2 * L) where N is number of reads and L is read length.
 * Space Complexity: O(N * L)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to find the length of the maximum overlap between two reads
int get_overlap(const string& a, const string& b) {
    int max_len = min(a.length(), b.length());
    // We look for a suffix of 'a' that is a prefix of 'b'
    // Start from the longest possible overlap (max_len - 1) down to 1
    for (int len = max_len - 1; len >= 1; --len) {
        if (a.substr(a.length() - len) == b.substr(0, len)) {
            return len;
        }
    }
    return 0;
}

string assemble_genome(vector<string>& reads) {
    int n = reads.size();
    vector<bool> visited(n, false);
    
    // Start with the first read
    int curr_idx = 0;
    visited[curr_idx] = true;
    string genome = reads[curr_idx];
    
    int first_read_idx = 0;
    int last_read_idx = 0;

    for (int i = 1; i < n; ++i) {
        int best_overlap = -1;
        int next_idx = -1;

        for (int j = 0; j < n; ++j) {
            if (!visited[j]) {
                int overlap = get_overlap(reads[curr_idx], reads[j]);
                if (overlap > best_overlap) {
                    best_overlap = overlap;
                    next_idx = j;
                }
            }
        }

        // Append the non-overlapping part of the next read
        genome += reads[next_idx].substr(best_overlap);
        visited[next_idx] = true;
        curr_idx = next_idx;
        last_read_idx = next_idx;
    }

    // Handle the circular overlap: find overlap between the last and first read
    int circular_overlap = get_overlap(reads[last_read_idx], reads[first_read_idx]);
    
    // Trim the duplicate part from the end
    if (circular_overlap > 0) {
        genome = genome.substr(0, genome.length() - circular_overlap);
    }

    return genome;
}

int main() {
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string read;
    
    // Read 1618 reads from standard input
    while (cin >> read) {
        // Only add unique reads (sometimes inputs have duplicates)
        if (find(reads.begin(), reads.end(), read) == reads.end()) {
            reads.push_back(read);
        }
    }

    if (reads.empty()) return 0;

    cout << assemble_genome(reads) << endl;

    return 0;
}
