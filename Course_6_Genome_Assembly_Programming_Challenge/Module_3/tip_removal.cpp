/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Dataset Problem - Tip Removal
 *
 * Logic:
 * We build a De Bruijn graph where edges are unique 15-mers and nodes are 14-mers.
 * A tip is identified as a node with (in_degree == 0 and out_degree > 0) OR 
 * (out_degree == 0 and in_degree > 0). We use a queue to iteratively remove 
 * the edges connected to these tips. If removing an edge creates a new tip, 
 * it is added to the queue for cascading removal.
 *
 * Time Complexity: O(V + E)
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // The problem specifies 15-mers for the dataset
    const int k = 15;
    
    unordered_set<string> unique_kmers;
    string read;
    
    // 1. Extract unique k-mers to act as edges
    while (cin >> read) {
        if (read.length() < k) continue;
        for (size_t i = 0; i <= read.length() - k; ++i) {
            unique_kmers.insert(read.substr(i, k));
        }
    }

    if (unique_kmers.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    unordered_map<string, int> str_to_id;
    int node_count = 0;

    auto get_id = [&](const string& s) {
        if (str_to_id.find(s) == str_to_id.end()) {
            str_to_id[s] = node_count++;
        }
        return str_to_id[s];
    };

    // 2. Build Adjacency Lists
    // Using unordered_set to easily erase specific neighbors
    vector<unordered_set<int>> out_edges;
    vector<unordered_set<int>> in_edges;

    for (const string& kmer : unique_kmers) {
        int u = get_id(kmer.substr(0, k - 1));
        int v = get_id(kmer.substr(1, k - 1));
        
        // Expand the adjacency lists dynamically if needed
        while (out_edges.size() <= max(u, v)) {
            out_edges.push_back({});
            in_edges.push_back({});
        }
        
        out_edges[u].insert(v);
        in_edges[v].insert(u);
    }

    // Helper lambda to determine if a node is currently a tip
    auto is_tip = [&](int u) {
        bool no_out = out_edges[u].empty();
        bool no_in = in_edges[u].empty();
        // A tip has zero edges on one side, but is connected on the other
        return (no_out && !no_in) || (!no_out && no_in);
    };

    // 3. Initialize the processing queue with all starting tips
    queue<int> Q;
    for (int i = 0; i < node_count; ++i) {
        if (is_tip(i)) {
            Q.push(i);
        }
    }

    int edges_removed = 0;

    // 4. Iteratively remove tips
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        // Check if it's an Out-Tip (End of a dead path)
        if (out_edges[u].empty() && !in_edges[u].empty()) {
            // Make a copy of in_edges because we are mutating the actual sets
            auto in_copy = in_edges[u];
            for (int p : in_copy) {
                // Remove the edge p -> u
                out_edges[p].erase(u);
                in_edges[u].erase(p);
                edges_removed++;
                
                // If removing this edge turned the parent 'p' into a tip, queue it
                if (is_tip(p)) {
                    Q.push(p);
                }
            }
        } 
        // Check if it's an In-Tip (Start of a dead path)
        else if (in_edges[u].empty() && !out_edges[u].empty()) {
            // Make a copy of out_edges
            auto out_copy = out_edges[u];
            for (int n : out_copy) {
                // Remove the edge u -> n
                in_edges[n].erase(u);
                out_edges[u].erase(n);
                edges_removed++;
                
                // If removing this edge turned the child 'n' into a tip, queue it
                if (is_tip(n)) {
                    Q.push(n);
                }
            }
        }
        // If it's completely isolated (both empty), it's ignored.
    }

    // Output the total number of edges removed during the process
    cout << edges_removed << "\n";

    return 0;
}
