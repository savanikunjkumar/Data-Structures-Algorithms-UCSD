/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 2 - Decomposition of Graphs 2
 * Assignment: Strongly Connected Components
 *
 * Logic: Kosaraju's Algorithm
 * 1. Compute the post-order traversal of the graph using DFS.
 * 2. Compute the reverse graph (all edges flipped).
 * 3. Run DFS on the reverse graph in the order of the reversed post-order stack.
 * Each new DFS call identifies a distinct Strongly Connected Component.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// DFS 1: Explores the original graph to determine the finish times (post-order)
void dfs1(int v, const vector<vector<int>> &adj, vector<bool> &used, stack<int> &order) {
    used[v] = true;
    for (int neighbor : adj[v]) {
        if (!used[neighbor]) {
            dfs1(neighbor, adj, used, order);
        }
    }
    // Push to stack only after all dependencies (neighbors) are fully explored
    order.push(v);
}

// DFS 2: Explores the reversed graph to mark all nodes in the current SCC
void dfs2(int v, const vector<vector<int>> &adj_rev, vector<bool> &used) {
    used[v] = true;
    for (int neighbor : adj_rev[v]) {
        if (!used[neighbor]) {
            dfs2(neighbor, adj_rev, used);
        }
    }
}

int number_of_strongly_connected_components(vector<vector<int>> &adj) {
    int n = adj.size();
    int result = 0;
    vector<bool> used(n, false);
    stack<int> order;

    // Step 1: Get the finish times using the original graph
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i, adj, used, order);
        }
    }

    // Step 2: Build the reversed graph
    vector<vector<int>> adj_rev(n, vector<int>());
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            adj_rev[v].push_back(u);
        }
    }

    // Step 3: Process nodes in decreasing order of finish times on the reversed graph
    fill(used.begin(), used.end(), false); // Reset the visited array for the second pass
    
    while (!order.empty()) {
        int v = order.top();
        order.pop();
        
        // If the node is unvisited, it's the start of a new SCC
        if (!used[v]) {
            dfs2(v, adj_rev, used);
            result++;
        }
    }

    return result;
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        // Convert from 1-based to 0-based indexing
        adj[x - 1].push_back(y - 1);
    }
    
    cout << number_of_strongly_connected_components(adj) << "\n";
    
    return 0;
}
