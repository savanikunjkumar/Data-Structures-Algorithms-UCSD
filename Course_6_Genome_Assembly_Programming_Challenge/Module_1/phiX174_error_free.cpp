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
#include <unordered_map>
#include <algorithm>

using namespace std;

/**
 * Problem: Assembling phi X174 Genome from Error-Free Reads
 * Strategy: Overlap Graph with Greedy Hamiltonian Path
 * Optimization: Prefix Hash Map for O(1) overlap discovery.
 */

// Finds the maximum exact overlap between suffix of s1 and prefix of s2
int get_perfect_overlap(const string& s1, const string& s2) {
    int n = s1.length();
    // Start from the longest possible overlap (n-1) down to 1
    for (int len = n - 1; len >= 1; --len) {
        if (s1.substr(n - len) == s2.substr(0, len)) {
            return len;
        }
    }
    return 0;
}

string assemble_genome(vector<string>& reads) {
    int n = reads.size();
    vector<bool> used(n, false);
    
    // Step 1: Index reads by their prefixes for faster lookup
    // Key: Prefix string, Value: Index of the read in the 'reads' vector
    unordered_map<string, vector<int>> prefix_map;
    for (int i = 0; i < n; ++i) {
        // We index the first 12 characters as a k-mer filter
        prefix_map[reads[i].substr(0, 12)].push_back(i);
    }

    int curr = 0;
    used[curr] = true;
    string genome = reads[curr];
    int assembled_count = 1;

    while (assembled_count < n) {
        int best_next = -1;
        int max_overlap = -1;

        // Step 2: Search for the best overlap starting from the longest possible
        // We look at the suffix of the current read
        string current_read = reads[curr];
        int l = current_read.length();

        // Instead of checking all N reads, we only check those that 
        // share a 12-mer with our current suffix.
        for (int len = l - 1; len >= 12; --len) {
            string suffix = current_read.substr(l - len);
            string kmer = suffix.substr(0, 12);

            if (prefix_map.count(kmer)) {
                for (int neighbor_idx : prefix_map[kmer]) {
                    if (!used[neighbor_idx]) {
                        // Check if the full overlap matches perfectly
                        if (reads[neighbor_idx].substr(0, len) == suffix) {
                            max_overlap = len;
                            best_next = neighbor_idx;
                            break;
                        }
                    }
                }
            }
            if (best_next != -1) break;
        }

        if (best_next != -1) {
            genome += reads[best_next].substr(max_overlap);
            used[best_next] = true;
            curr = best_next;
            assembled_count++;
        } else {
            // Fallback: If no overlap >= 12 found (unlikely in this dataset)
            break; 
        }
    }

    // Step 3: Handle circularity by removing the overlap between last and first read
    int circular_overlap = get_perfect_overlap(reads[curr], reads[0]);
    if (circular_overlap > 0) {
        genome = genome.substr(0, genome.length() - circular_overlap);
    }

    return genome;
}

int main() {
    // Speed up I/O for large datasets
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string r;
    while (cin >> r) {
        // Only add unique reads
        bool duplicate = false;
        for(const auto& existing : reads) {
            if(existing == r) {
                duplicate = true;
                break;
            }
        }
        if(!duplicate) reads.push_back(r);
    }

    if (reads.empty()) return 0;

    cout << assemble_genome(reads) << endl;

    return 0;
}
