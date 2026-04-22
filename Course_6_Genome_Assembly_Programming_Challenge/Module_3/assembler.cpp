/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Final Project - Implementing an Assembler
 *
 * Logic:
 * This is a complete, memory-optimized De Bruijn Graph Assembler. 
 * It dynamically sizes k, parses both single and paired-end reads, maps 
 * string nodes to integer IDs to prevent Out-Of-Memory (OOM) errors, 
 * and extracts all Maximal Non-Branching Paths to generate FASTA contigs.
 *
 * Time Complexity: O(N * L) where N is the number of reads and L is length.
 * Space Complexity: O(U * L) where U is the number of unique (k-1)-mers.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Structure to track directed edges
struct Edge {
    int from;
    int to;
};

int main() {
    // Fast I/O is absolutely critical for parsing 1.4 million reads
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (!(cin >> t)) return 0;

    vector<string> reads;
    string line;
    int min_len = 1e9; // Start with a very high number

    // 1. Parse Input Data
    for (int i = 0; i < t; ++i) {
        cin >> line;
        size_t pos1 = line.find('|');
        if (pos1 != string::npos) {
            // It's a read-pair: READ1|READ2|d
            size_t pos2 = line.find('|', pos1 + 1);
            string r1 = line.substr(0, pos1);
            string r2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
            reads.push_back(r1);
            reads.push_back(r2);
            min_len = min({min_len, (int)r1.length(), (int)r2.length()});
        } else {
            // It's a single read
            reads.push_back(line);
            min_len = min(min_len, (int)line.length());
        }
    }

    if (reads.empty()) return 0;

    // Set k to the length of the shortest read in the dataset
    int k = min_len;

    // 2. Memory Optimization: Map strings to integer IDs
    unordered_map<string, int> str_to_id;
    vector<string> id_to_str;

    auto get_id = [&](const string& s) {
        auto it = str_to_id.find(s);
        if (it != str_to_id.end()) return it->second;
        int id = id_to_str.size();
        str_to_id[s] = id;
        id_to_str.push_back(s);
        return id;
    };

    vector<Edge> edges;
    
    // Break reads into edges (k-mers) and nodes ((k-1)-mers)
    for (const string& read : reads) {
        for (size_t i = 0; i <= read.length() - k; ++i) {
            string prefix = read.substr(i, k - 1);
            string suffix = read.substr(i + 1, k - 1);
            int u = get_id(prefix);
            int v = get_id(suffix);
            edges.push_back({u, v});
        }
    }

    int n_nodes = id_to_str.size();
    vector<vector<int>> adj(n_nodes);
    vector<int> out_degree(n_nodes, 0);
    vector<int> in_degree(n_nodes, 0);

    // Build the mathematical graph
    for (size_t i = 0; i < edges.size(); ++i) {
        adj[edges[i].from].push_back(i);
        out_degree[edges[i].from]++;
        in_degree[edges[i].to]++;
    }

    // 3. Find Maximal Non-Branching Paths
    vector<bool> edge_used(edges.size(), false);
    int contig_id = 1;

    // A node is a straight path if it has exactly 1 incoming and 1 outgoing edge
    auto is_1_in_1_out = [&](int v) {
        return in_degree[v] == 1 && out_degree[v] == 1;
    };

    // First pass: Start contigs from branching nodes or dead ends
    for (int v = 0; v < n_nodes; ++v) {
        if (!is_1_in_1_out(v)) {
            if (out_degree[v] > 0) {
                for (int edge_id : adj[v]) {
                    if (edge_used[edge_id]) continue;

                    edge_used[edge_id] = true;
                    // Start building the string
                    string contig = id_to_str[v] + id_to_str[edges[edge_id].to].back();
                    int curr = edges[edge_id].to;

                    // Walk down the path as long as nodes are 1-in-1-out
                    while (is_1_in_1_out(curr)) {
                        int next_edge = -1;
                        for (int e : adj[curr]) {
                            if (!edge_used[e]) {
                                next_edge = e;
                                break;
                            }
                        }
                        if (next_edge == -1) break; // Should be impossible if 1-in-1-out, but safe

                        edge_used[next_edge] = true;
                        contig += id_to_str[edges[next_edge].to].back();
                        curr = edges[next_edge].to;
                    }

                    // Output in FASTA format
                    cout << ">CONTIG" << contig_id++ << "\n" << contig << "\n";
                }
            }
        }
    }

    // Second pass: Find completely isolated cycles (circular genomes with no branching)
    for (size_t i = 0; i < edges.size(); ++i) {
        if (!edge_used[i]) {
            edge_used[i] = true;
            string contig = id_to_str[edges[i].from] + id_to_str[edges[i].to].back();
            int curr = edges[i].to;
            int start = edges[i].from;

            while (curr != start) {
                int next_edge = -1;
                for (int e : adj[curr]) {
                    if (!edge_used[e]) {
                        next_edge = e;
                        break;
                    }
                }
                if (next_edge == -1) break;

                edge_used[next_edge] = true;
                contig += id_to_str[edges[next_edge].to].back();
                curr = edges[next_edge].to;
            }

            cout << ">CONTIG" << contig_id++ << "\n" << contig << "\n";
        }
    }

    return 0;
}
