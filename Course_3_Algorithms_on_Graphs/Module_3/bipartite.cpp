/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 3 - Paths in Graph 1
 * Assignment: Checking if a Graph is Bipartite
 *
 * Logic: BFS Graph 2-Coloring
 * We attempt to color the graph using two colors (0 and 1) via BFS.
 * If we ever find an edge connecting two nodes of the same color, 
 * the graph is not bipartite. We loop through all nodes to account 
 * for disconnected components.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bipartite(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> color(n, -1);

    // Loop handles disconnected graph components
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0; // Start coloring with color 0

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int neighbor : adj[u]) {
                    // If neighbor is uncolored, assign it the opposite color
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[u];
                        q.push(neighbor);
                    } 
                    // If neighbor has the same color as the current node, it's not bipartite
                    else if (color[neighbor] == color[u]) {
                        return 0;
                    }
                }
            }
        }
    }
    
    // Successfully colored the entire graph
    return 1;
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        // Convert 1-based indexing to 0-based
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    cout << bipartite(adj) << "\n";
    
    return 0;
}
