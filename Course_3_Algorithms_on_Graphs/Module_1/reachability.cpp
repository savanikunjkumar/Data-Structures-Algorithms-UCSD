/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs (Course 3)
 * Module: Module 1 - Decomposition of Graphs 1
 * Assignment: Reachability
 *
 * Logic: 
 * We use DFS to explore all reachable nodes from vertex x. 
 * If vertex y is visited during this exploration, we return 1.
 * Time Complexity: O(V + E) where V is vertices and E is edges.
 * Space Complexity: O(V) for the visited array and recursion stack.
 */

#include <iostream>
#include <vector>

using namespace std;

// DFS helper function to explore the graph
void dfs(vector<vector<int>> &adj, int x, vector<bool> &visited) {
    visited[x] = true;
    for (int neighbor : adj[x]) {
        if (!visited[neighbor]) {
            dfs(adj, neighbor, visited);
        }
    }
}

int reach(vector<vector<int>> &adj, int x, int y) {
    int n = adj.size();
    vector<bool> visited(n, false);
    
    // Start traversal from vertex x
    dfs(adj, x, visited);
    
    // If y was marked as visited, a path exists
    return visited[y] ? 1 : 0;
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n, m;
    if (!(cin >> n >> m)) return 0;

    // Adjacency list representation
    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        // Convert 1-based indexing to 0-based
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    int x, y;
    cin >> x >> y;
    
    // Subtract 1 from x and y for 0-based indexing
    cout << reach(adj, x - 1, y - 1) << endl;

    return 0;
}
