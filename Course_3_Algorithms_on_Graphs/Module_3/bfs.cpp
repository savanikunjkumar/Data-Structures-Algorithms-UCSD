/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 3 - Paths in Graph 1
 * Assignment: Computing the Minimum Number of Flight Segments
 *
 * Logic: Breadth-First Search (BFS)
 * In an unweighted graph, the shortest path between two nodes is found using BFS.
 * We use a queue to explore nodes level by level, maintaining a distance array 
 * initialized to -1. When we discover a new unvisited neighbor, its distance is 
 * simply the current node's distance + 1.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int distance(vector<vector<int>> &adj, int s, int t) {
    // If the start node is the target node, distance is 0
    if (s == t) return 0;

    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;

    // Start BFS from node 's'
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int neighbor : adj[u]) {
            // If the neighbor hasn't been visited yet
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[u] + 1;
                
                // Optimization: If we found the target, exit early
                if (neighbor == t) {
                    return dist[t];
                }
                
                q.push(neighbor);
            }
        }
    }
    
    // Target is unreachable from start
    return -1;
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
    
    int s, t;
    cin >> s >> t;
    
    // Adjust start and target to 0-based indexing
    cout << distance(adj, s - 1, t - 1) << "\n";
    
    return 0;
}
