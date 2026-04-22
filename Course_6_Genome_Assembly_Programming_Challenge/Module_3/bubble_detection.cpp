/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Dataset Problem - Bubble Detection
 *
 * Logic: Bounded DFS with Disjoint Checking
 * We construct a unique-edge de Bruijn graph to eliminate trivial parallel edges.
 * For every node with out-degree >= 2, we perform a DFS limited by depth 't'.
 * All paths are grouped by their destination node. We then pairwise-compare
 * these paths to count how many are strictly disjoint (sharing no intermediate nodes).
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Checks if two paths share any intermediate nodes
// Paths exclude 'v' but include 'w'. Thus, the last element is always 'w'.
// Intermediate nodes are indices 0 to size-2.
bool are_disjoint(const vector<int>& p1, const vector<int>& p2) {
    for (size_t i = 0; i + 1 < p1.size(); ++i) {
        for (size_t j = 0; j + 1 < p2.size(); ++j) {
            if (p1[i] == p2[j]) {
                return false;
            }
        }
    }
    return true;
}

// Bounded DFS to find all non-overlapping paths of length <= t
void dfs(int u, int depth, int t, vector<int>& curr_path, vector<bool>& visited, 
         vector<vector<vector<int>>>& paths_to, vector<int>& active_w, 
         const vector<vector<int>>& adj) {
             
    if (depth == t) return;

    for (int nxt : adj[u]) {
        if (!visited[nxt]) {
            visited[nxt] = true;
            curr_path.push_back(nxt);
            
            // If this is the first path reaching 'nxt' from our starting 'v', record 'nxt'
            if (paths_to[nxt].empty()) {
                active_w.push_back(nxt);
            }
            paths_to[nxt].push_back(curr_path);
            
            dfs(nxt, depth + 1, t, curr_path, visited, paths_to, active_w, adj);
            
            // Backtrack
            curr_path.pop_back();
            visited[nxt] = false;
        }
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, t;
    if (!(cin >> k >> t)) return 0;

    unordered_set<string> unique_kmers;
    string read;
    
    // 1. Extract unique k-mers to form unique edges
    while (cin >> read) {
        for (size_t i = 0; i <= read.length() - k; ++i) {
            unique_kmers.insert(read.substr(i, k));
        }
    }

    if (unique_kmers.empty()) return 0;

    unordered_map<string, int> str_to_id;
    int node_count = 0;

    auto get_id = [&](const string& s) {
        if (str_to_id.find(s) == str_to_id.end()) {
            str_to_id[s] = node_count++;
        }
        return str_to_id[s];
    };

    vector<pair<int, int>> edges;
    for (const string& kmer : unique_kmers) {
        int u = get_id(kmer.substr(0, k - 1));
        int v = get_id(kmer.substr(1, k - 1));
        edges.push_back({u, v});
    }

    // 2. Build Adjacency List
    vector<vector<int>> adj(node_count);
    for (const auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
    }

    long long total_bubbles = 0;
    
    // Pre-allocate memory for DFS state tracking to avoid massive re-allocations
    vector<vector<vector<int>>> paths_to(node_count);
    vector<bool> visited(node_count, false);
    vector<int> active_w;
    vector<int> curr_path;

    // 3. Search for bubbles
    for (int v = 0; v < node_count; ++v) {
        // Optimization: A bubble MUST diverge from 'v', so out-degree must be >= 2
        if (adj[v].size() < 2) continue;

        visited[v] = true; // Mark start node as visited
        dfs(v, 0, t, curr_path, visited, paths_to, active_w, adj);
        visited[v] = false; // Unmark for the next global iteration

        // 4. Count disjoint pairs for all reached destinations 'w'
        for (int w : active_w) {
            const auto& paths = paths_to[w];
            if (paths.size() >= 2) {
                for (size_t i = 0; i < paths.size(); ++i) {
                    for (size_t j = i + 1; j < paths.size(); ++j) {
                        if (are_disjoint(paths[i], paths[j])) {
                            total_bubbles++;
                        }
                    }
                }
            }
            // Clear the paths for this 'w' to prep for the next starting node 'v'
            paths_to[w].clear();
        }
        active_w.clear();
    }

    cout << total_bubbles << "\n";

    return 0;
}
