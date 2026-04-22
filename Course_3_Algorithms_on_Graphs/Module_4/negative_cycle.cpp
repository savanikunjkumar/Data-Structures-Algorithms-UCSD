/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Assignment: Detecting Anomalies (Negative Cycles)
 *
 * Logic: SPFA (Shortest Path Faster Algorithm)
 * An optimized version of Bellman-Ford. We use a queue to only relax edges
 * of vertices whose shortest distance has recently changed. We also track
 * how many times a vertex enters the queue; if it hits 'V' times, a 
 * negative cycle exists.
 *
 * Time Complexity: O(V * E) worst case, but O(E) on average.
 * Space Complexity: O(V)
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost) {
    int n = adj.size();
    
    // Initialize distances to 0 to catch disconnected negative cycles
    vector<long long> dist(n, 0);
    
    // Tracks how many times a node is added to the queue
    vector<int> count(n, 0);
    
    // Tracks if a node is currently in the queue to prevent duplicates
    vector<bool> in_queue(n, true); 
    
    queue<int> q;

    // Push all nodes initially to handle disconnected components
    for (int i = 0; i < n; i++) {
        q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            long long weight = cost[u][i];

            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                
                // Only push to queue if it's not already in there
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                    count[v]++;
                    
                    // If a node is updated V times, a negative cycle exists
                    if (count[v] >= n) {
                        return 1;
                    }
                }
            }
        }
    }

    // Queue emptied without any node hitting V updates
    return 0;
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> cost(n, vector<int>());
    
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    
    cout << negative_cycle(adj, cost) << "\n";
    
    return 0;
}
