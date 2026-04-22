/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 2 - Assembling Genomes Using De Bruijn Graphs
 * Assignment: Assembling the phi X174 Genome from its k-mer Composition
 *
 * Logic: De Bruijn Graph + Eulerian Cycle
 * 1. Parse each k-mer into a (k-1)-mer prefix and suffix.
 * 2. Assign unique integer IDs to each unique (k-1)-mer to build an adjacency list.
 * 3. Add a directed edge from prefix to suffix for each k-mer.
 * 4. Run Hierholzer's Algorithm to find the Eulerian cycle.
 * 5. Reconstruct the circular string from the cycle of nodes.
 *
 * Time Complexity: O(N) where N is the number of k-mers.
 * Space Complexity: O(N) to store the graph and string mappings.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

// Globals for mapping strings to integer IDs
unordered_map<string, int> str_to_id;
vector<string> id_to_str;

// Function to get or create an ID for a (k-1)-mer
int get_id(const string& s) {
    if (str_to_id.find(s) == str_to_id.end()) {
        str_to_id[s] = id_to_str.size();
        id_to_str.push_back(s);
    }
    return str_to_id[s];
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string kmer;
    struct Edge { int u, v; };
    vector<Edge> edges;

    // 1. Read all k-mers and define the edges
    while (cin >> kmer) {
        string prefix = kmer.substr(0, kmer.length() - 1);
        string suffix = kmer.substr(1);
        
        int u = get_id(prefix);
        int v = get_id(suffix);
        edges.push_back({u, v});
    }

    if (edges.empty()) return 0;

    // 2. Build the Adjacency List
    int num_nodes = id_to_str.size();
    vector<vector<int>> adj(num_nodes);
    for (const auto& e : edges) {
        adj[e.u].push_back(e.v);
    }

    // 3. Hierholzer's Algorithm to find Eulerian Cycle
    stack<int> st;
    vector<int> path;
    
    // The graph is guaranteed to be strongly connected and balanced
    st.push(0); 

    while (!st.empty()) {
        int u = st.top();
        
        if (!adj[u].empty()) {
            int v = adj[u].back();
            adj[u].pop_back();
            st.push(v);
        } else {
            path.push_back(u);
            st.pop();
        }
    }

    // Path is built backwards
    reverse(path.begin(), path.end());

    // 4. Reconstruct the Circular Genome
    // The cycle visits N+1 nodes (starting and ending at the same node).
    // We only need the first character of the first N nodes to form the genome.
    string genome = "";
    for (size_t i = 0; i < path.size() - 1; ++i) {
        genome += id_to_str[path[i]][0];
    }

    cout << genome << "\n";

    return 0;
}
