/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs (Course 3)
 * Module: Module 1 - Decomposition of Graphs 1
 * Assignment: Number of Connected Components
 *
 * Logic:
 * We iterate through all nodes. For every unvisited node, we start a DFS.
 * Each time a new DFS starts from the main loop, it represents a distinct 
 * connected component.
 * * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the visited array and recursion stack.
 */

#include <iostream>
#include <vector>

using namespace std;

// DFS helper to mark all nodes in the current component as visited
void explore(int v, const vector<vector<int>> &adj, vector<bool> &visited) {
    visited[v] = true;
    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            explore(neighbor, adj, visited);
        }
    }
}

int number_of_components(vector<vector<int>> &adj) {
    int res = 0;
    int n = adj.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) {
        // If the node hasn't been reached by a previous DFS, 
        // it belongs to a new connected component.
        if (!visited[i]) {
            res++;
            explore(i, adj, visited);
        }
    }
    return res;
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
        // Adjusting 1-based indexing to 0-based
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    cout << number_of_components(adj) << endl;

    return 0;
}
