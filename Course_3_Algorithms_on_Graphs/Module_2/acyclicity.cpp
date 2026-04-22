/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs (Course 3)
 * Module: Module 2 - Decomposition of Graphs 2
 * Assignment: Checking Consistency (Acyclicity)
 *
 * Logic:
 * A directed graph has a cycle if and only if a DFS reveals a back edge.
 * We maintain a 'recursionStack' to track nodes in the current DFS path.
 * If we encounter a node already in the recursion stack, a cycle exists.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */

#include <iostream>
#include <vector>

using namespace std;

// DFS helper to detect cycles
bool hasCycle(int v, const vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &recursionStack) {
    // Mark the current node as visited and part of the current recursion path
    visited[v] = true;
    recursionStack[v] = true;

    for (int neighbor : adj[v]) {
        // If neighbor is already in the current path, we found a back edge (cycle)
        if (recursionStack[neighbor]) {
            return true;
        }
        // If neighbor hasn't been visited, recurse
        if (!visited[neighbor]) {
            if (hasCycle(neighbor, adj, visited, recursionStack)) {
                return true;
            }
        }
    }

    // Remove the node from the recursion stack before backtracking
    recursionStack[v] = false;
    return false;
}

int acyclic(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<bool> recursionStack(n, false);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (hasCycle(i, adj, visited, recursionStack)) {
                return 1; // Cycle detected
            }
        }
    }
    return 0; // No cycles found
}

int main() {
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        // Directed edge: x -> y (0-based indexing)
        adj[x - 1].push_back(y - 1);
    }

    cout << acyclic(adj) << endl;

    return 0;
}
