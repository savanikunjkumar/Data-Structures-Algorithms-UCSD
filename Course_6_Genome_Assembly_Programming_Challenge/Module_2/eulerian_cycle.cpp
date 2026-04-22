/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 2 - Assembling Genomes Using De Bruijn Graphs
 * Assignment: Finding an Eulerian Cycle in Directed Graph
 *
 * Logic: Hierholzer’s Algorithm
 * 1. Verify in-degree == out-degree for all nodes.
 * 2. Perform a DFS-based traversal, removing edges as they are used.
 * 3. Use a stack to store the path and backtrack when a node's edges 
 * are exhausted.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Edge {
    int to;
};

int main() {
    // Fast I/O is mandatory for 10^5 edges
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);
    vector<int> out_degree(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        out_degree[u]++;
        in_degree[v]++;
    }

    // Condition 1: Check if in-degree equals out-degree for every vertex
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] != out_degree[i]) {
            cout << 0 << endl;
            return 0;
        }
    }

    // Hierholzer's Algorithm
    vector<int> cycle;
    stack<int> curr_path;
    
    // Find a starting node with outgoing edges
    int start_node = 1;
    for (int i = 1; i <= n; i++) {
        if (out_degree[i] > 0) {
            start_node = i;
            break;
        }
    }

    curr_path.push(start_node);
    
    while (!curr_path.empty()) {
        int u = curr_path.top();
        
        if (!adj[u].empty()) {
            // Pick an edge, remove it, and move to next node
            int v = adj[u].back();
            adj[u].pop_back();
            curr_path.push(v);
        } else {
            // Backtrack: add to cycle and pop from stack
            cycle.push_back(u);
            curr_path.pop();
        }
    }

    // Condition 2: Check if all edges were used
    // The cycle should have m+1 vertices (start...end)
    // The problem asks for m vertices (v1...vm)
    if (cycle.size() != m + 1) {
        cout << 0 << endl;
        return 0;
    }

    // Successful finding
    cout << 1 << "\n";
    // The path is stored in reverse order in our vector
    reverse(cycle.begin(), cycle.end());
    
    // Output the first m vertices of the cycle
    for (int i = 0; i < m; i++) {
        cout << cycle[i] << (i == m - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
