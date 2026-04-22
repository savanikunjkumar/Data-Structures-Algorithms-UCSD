/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 4 - Paths in Graph 2
 * Assignment: Exchanging Money Optimally (Shortest Paths)
 *
 * Logic: Bellman-Ford + BFS
 * 1. Run Bellman-Ford V-1 times to find initial shortest paths.
 * 2. Run a V-th iteration to find nodes directly affected by a negative cycle and add them to a queue.
 * 3. Run a BFS from the queue to mark all downstream nodes as having no shortest path (-∞).
 *
 * Time Complexity: O(V * E)
 * Space Complexity: O(V)
 */

#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using namespace std;

void shortest_paths(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
    int n = adj.size();
    const long long INF = numeric_limits<long long>::max();
    
    // Initialize the start node
    distance[s] = 0;
    reachable[s] = 1;

    // Phase 1: Relax all edges V - 1 times
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            // Only relax if the node 'u' is actually reachable from the start
            if (distance[u] != INF) {
                for (size_t k = 0; k < adj[u].size(); k++) {
                    int v = adj[u][k];
                    long long w = cost[u][k];
                    
                    if (distance[u] + w < distance[v]) {
                        distance[v] = distance[u] + w;
                        reachable[v] = 1;
                    }
                }
            }
        }
    }

    queue<int> q;
    vector<int> in_queue(n, 0);

    // Phase 2: Run the V-th iteration to find nodes directly in negative cycles
    for (int u = 0; u < n; u++) {
        if (distance[u] != INF) {
            for (size_t k = 0; k < adj[u].size(); k++) {
                int v = adj[u][k];
                long long w = cost[u][k];
                
                // If it can STILL be relaxed, it's affected by a negative cycle
                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w; // Update to prevent re-triggering unnecessarily
                    if (!in_queue[v]) {
                        q.push(v);
                        in_queue[v] = 1;
                    }
                }
            }
        }
    }

    // Phase 3: BFS to propagate the negative cycle effect downstream
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        // Mark as having no well-defined shortest path
        shortest[u] = 0;

        for (size_t k = 0; k < adj[u].size(); k++) {
            int v = adj[u][k];
            
            // If we haven't already marked this neighbor, add it to the queue
            if (shortest[v] != 0 && !in_queue[v]) {
                q.push(v);
                in_queue[v] = 1;
                shortest[v] = 0;
            }
        }
    }
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> cost(n, vector<int>());
    
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        // Convert 1-based indexing to 0-based
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    
    cin >> s;
    s--; // Adjust start node to 0-based
    
    vector<long long> distance(n, numeric_limits<long long>::max());
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            cout << "*\n";
        } else if (!shortest[i]) {
            cout << "-\n";
        } else {
            cout << distance[i] << "\n";
        }
    }
    
    return 0;
}
