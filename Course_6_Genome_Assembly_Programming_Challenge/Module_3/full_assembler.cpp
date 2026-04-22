/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Dataset Problem - Assembling the phi X174 Genome from Error-Prone Reads
 *
 * Logic: The Complete Assembly Pipeline
 * 1. Build a weighted De Bruijn graph from 15-mers.
 * 2. Iteratively remove tips using a queue.
 * 3. Detect and remove bubbles by prioritizing high-coverage paths.
 * 4. Extract the final Eulerian cycle to form the circular genome.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    bool valid;
};

int n_nodes = 0;
vector<Edge> edges;
vector<vector<int>> adj;
vector<vector<int>> in_adj;
vector<int> out_degree;
vector<int> in_degree;

bool remove_tips() {
    bool changed = false;
    queue<int> q;
    
    // Identify all initial tips
    for (int i = 0; i < n_nodes; ++i) {
        if ((in_degree[i] == 0 && out_degree[i] > 0) || (in_degree[i] > 0 && out_degree[i] == 0)) {
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        
        // Remove outgoing edges
        for (int edge_id : adj[u]) {
            if (edges[edge_id].valid) {
                edges[edge_id].valid = false;
                changed = true;
                out_degree[u]--;
                int v = edges[edge_id].to;
                in_degree[v]--;
                if ((in_degree[v] == 0 && out_degree[v] > 0) || (in_degree[v] > 0 && out_degree[v] == 0)) {
                    q.push(v);
                }
            }
        }
        
        // Remove incoming edges
        for (int edge_id : in_adj[u]) {
            if (edges[edge_id].valid) {
                edges[edge_id].valid = false;
                changed = true;
                in_degree[u]--;
                int p = edges[edge_id].from;
                out_degree[p]--;
                if ((in_degree[p] == 0 && out_degree[p] > 0) || (in_degree[p] > 0 && out_degree[p] == 0)) {
                    q.push(p);
                }
            }
        }
    }
    return changed;
}

bool remove_bubbles() {
    int t = 20; // Depth threshold for bubble detection
    
    for (int v = 0; v < n_nodes; ++v) {
        if (out_degree[v] > 1) {
            vector<vector<vector<int>>> paths_to(n_nodes);
            vector<int> curr_path;
            vector<bool> visited(n_nodes, false);
            visited[v] = true;

            // Bounded DFS to find paths
            auto dfs = [&](auto& self, int u, int depth) -> void {
                if (depth == t) return;
                for (int edge_id : adj[u]) {
                    if (!edges[edge_id].valid) continue;
                    int nxt = edges[edge_id].to;
                    if (!visited[nxt]) {
                        visited[nxt] = true;
                        curr_path.push_back(edge_id);
                        paths_to[nxt].push_back(curr_path);
                        self(self, nxt, depth + 1);
                        curr_path.pop_back();
                        visited[nxt] = false;
                    }
                }
            };

            dfs(dfs, v, 0);

            // Check for bubbles and resolve them
            for (int w = 0; w < n_nodes; ++w) {
                if (paths_to[w].size() > 1) {
                    for (size_t i = 0; i < paths_to[w].size(); ++i) {
                        for (size_t j = i + 1; j < paths_to[w].size(); ++j) {
                            const auto& p1 = paths_to[w][i];
                            const auto& p2 = paths_to[w][j];
                            
                            // Check if paths are disjoint
                            bool disjoint = true;
                            unordered_set<int> nodes1;
                            for (size_t k = 0; k + 1 < p1.size(); ++k) nodes1.insert(edges[p1[k]].to);
                            for (size_t k = 0; k + 1 < p2.size(); ++k) {
                                if (nodes1.count(edges[p2[k]].to)) {
                                    disjoint = false;
                                    break;
                                }
                            }

                            if (disjoint) {
                                // Calculate average coverage/weight
                                double w1 = 0, w2 = 0;
                                for (int e : p1) w1 += edges[e].weight;
                                w1 /= p1.size();
                                for (int e : p2) w2 += edges[e].weight;
                                w2 /= p2.size();

                                // Remove the path with lower coverage
                                const vector<int>& to_remove = (w1 < w2) ? p1 : p2;
                                for (int e : to_remove) {
                                    if (edges[e].valid) {
                                        edges[e].valid = false;
                                        out_degree[edges[e].from]--;
                                        in_degree[edges[e].to]--;
                                    }
                                }
                                return true; // Restart to maintain graph integrity
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k = 15;
    unordered_map<string, int> kmer_counts;
    string read;
    
    // 1. Read input and count 15-mer frequencies
    while (cin >> read) {
        if (read.length() < k) continue;
        for (size_t i = 0; i <= read.length() - k; ++i) {
            kmer_counts[read.substr(i, k)]++;
        }
    }

    if (kmer_counts.empty()) return 0;

    unordered_map<string, int> str_to_id;
    vector<string> id_to_str;

    auto get_id = [&](const string& s) {
        auto it = str_to_id.find(s);
        if (it == str_to_id.end()) {
            int id = id_to_str.size();
            str_to_id[s] = id;
            id_to_str.push_back(s);
            return id;
        }
        return it->second;
    };

    // 2. Build the Graph
    for (const auto& pair : kmer_counts) {
        string kmer = pair.first;
        int count = pair.second;
        
        int u = get_id(kmer.substr(0, k - 1));
        int v = get_id(kmer.substr(1, k - 1));
        
        int edge_id = edges.size();
        edges.push_back({u, v, count, true});
    }

    n_nodes = id_to_str.size();
    adj.resize(n_nodes);
    in_adj.resize(n_nodes);
    in_degree.assign(n_nodes, 0);
    out_degree.assign(n_nodes, 0);

    for (size_t i = 0; i < edges.size(); ++i) {
        adj[edges[i].from].push_back(i);
        in_adj[edges[i].to].push_back(i);
        out_degree[edges[i].from]++;
        in_degree[edges[i].to]++;
    }

    // 3. Clean the Graph (Error Correction loop)
    while (true) {
        bool tips_removed = remove_tips();
        bool bubbles_removed = remove_bubbles();
        if (!tips_removed && !bubbles_removed) break;
    }

    // 4. Find the Eulerian Cycle
    stack<int> st;
    vector<int> cycle;
    
    // Find a valid starting node
    int start = -1;
    for (int i = 0; i < n_nodes; ++i) {
        if (out_degree[i] > 0) {
            start = i;
            break;
        }
    }

    if (start != -1) {
        st.push(start);
        while (!st.empty()) {
            int u = st.top();
            bool found = false;
            
            while (!adj[u].empty()) {
                int edge_id = adj[u].back();
                adj[u].pop_back(); // Consume the edge
                if (edges[edge_id].valid) {
                    st.push(edges[edge_id].to);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cycle.push_back(u);
                st.pop();
            }
        }
        reverse(cycle.begin(), cycle.end());
    }

    // 5. Reconstruct the circular genome
    string genome = "";
    if (!cycle.empty()) {
        for (size_t i = 0; i < cycle.size() - 1; ++i) {
            genome += id_to_str[cycle[i]][0];
        }
    }

    cout << genome << "\n";

    return 0;
}
