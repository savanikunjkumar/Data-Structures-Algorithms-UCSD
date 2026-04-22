/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Dataset Problem - Selecting the Optimal k-mer Size
 *
 * Logic:
 * We iterate k downwards from 100. For each k, we construct a De Bruijn 
 * graph using all unique k-mers from the reads. The graph has a unique 
 * Eulerian cycle if and only if every (k-1)-mer node has exactly an 
 * in-degree of 1 and an out-degree of 1, and the entire graph forms a 
 * single connected component.
 *
 * Time Complexity: O(R * L) where R is reads and L is read length.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main() {
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<string> reads;
    string s;
    while (cin >> s) {
        reads.push_back(s);
    }

    if (reads.empty()) return 0;

    int read_length = reads[0].length();

    // Iterate k downwards from read_length
    for (int k = read_length; k >= 2; --k) {
        unordered_set<string> kmers;
        
        // 1. Extract all unique k-mers
        for (const string& read : reads) {
            for (int i = 0; i <= read_length - k; ++i) {
                kmers.insert(read.substr(i, k));
            }
        }

        unordered_map<string, int> in_deg, out_deg;
        unordered_set<string> nodes;
        unordered_map<string, string> next_node;

        // 2. Build the De Bruijn Graph properties
        for (const string& kmer : kmers) {
            string prefix = kmer.substr(0, k - 1);
            string suffix = kmer.substr(1, k - 1);
            
            nodes.insert(prefix);
            nodes.insert(suffix);
            
            out_deg[prefix]++;
            in_deg[suffix]++;
            next_node[prefix] = suffix; // Since we aim for out_deg == 1, storing one edge is enough
        }

        // 3. Verify the 1-in, 1-out property for all nodes
        bool is_simple_cycle = true;
        for (const string& node : nodes) {
            if (in_deg[node] != 1 || out_deg[node] != 1) {
                is_simple_cycle = false;
                break;
            }
        }

        if (!is_simple_cycle) continue;

        // 4. Verify Single Connected Component
        // Since every node has 1 in and 1 out, it must be a set of disjoint cycles.
        // We just need to check if tracking one cycle visits ALL nodes.
        string start_node = *nodes.begin();
        string curr_node = start_node;
        int visited_count = 0;
        
        do {
            curr_node = next_node[curr_node];
            visited_count++;
        } while (curr_node != start_node && visited_count <= nodes.size());

        // If the cycle length equals the total number of unique (k-1)-mers, it's a single Eulerian cycle!
        if (curr_node == start_node && visited_count == nodes.size()) {
            cout << k << "\n";
            return 0;
        }
    }

    return 0;
}
