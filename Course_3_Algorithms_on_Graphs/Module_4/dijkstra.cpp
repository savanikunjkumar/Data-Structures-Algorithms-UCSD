/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 4 - Paths in Graph 2
 * Assignment: Computing the Minimum Cost of a Flight
 *
 * Logic: Dijkstra's Algorithm
 * For graphs with weighted edges, BFS no longer guarantees the shortest path.
 * We use Dijkstra's algorithm with a Min-Priority Queue to always expand the
 * closest unvisited node. This guarantees the minimum total cost path.
 *
 * Time Complexity: O((V + E) log V)
 * Space Complexity: O(V)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Alias for readability: pair of (distance, node_index)
typedef pair<long long, int> pii; 

long long distance(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, int t) {
    int n = adj.size();
    
    // Initialize distances to "Infinity"
    const long long INF = numeric_limits<long long>::max();
    vector<long long> dist(n, INF);

    // Min-priority queue to always process the closest reachable node first
    // greater<pii> ensures the smallest distance is at the top
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Start node distance is 0
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        pii top = pq.top();
        pq.pop();
        
        long long current_dist = top.first;
        int u = top.second;

        // Optimization 1: If we reached the target, we can stop early
        if (u == t) {
            return current_dist;
        }

        // Optimization 2: Ignore stale pairs in the priority queue
        if (current_dist > dist[u]) {
            continue;
        }

        // Relax all outbound edges from u
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            long long weight = cost[u][i];

            // If we found a shorter path to v
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // If the target remains at Infinity, it's unreachable
    return dist[t] == INF ? -1 : dist[t];
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    
    // Using adjacency lists for both graph edges and their respective costs
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> cost(n, vector<int>());
    
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        // Convert 1-based indexing to 0-based
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    
    int s, t;
    cin >> s >> t;
    
    // Adjust start and target to 0-based indexing
    cout << distance(adj, cost, s - 1, t - 1) << "\n";
    
    return 0;
}
