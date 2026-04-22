/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 1 - Flows in Networks
 * Assignment: Evacuating People (Maximum Flow)
 *
 * Logic: Edmonds-Karp Algorithm
 * We use BFS to find the shortest augmenting path in the residual graph. 
 * This prevents the slow convergence issue seen in basic Ford-Fulkerson 
 * when dealing with large edge capacities.
 *
 * Time Complexity: O(V * E^2)
 * Space Complexity: O(V + E)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to represent a directed edge in the flow network
struct Edge {
    int from, to, capacity, flow;
};

// Flow network class using an adjacency list of edge indices
class FlowNetwork {
    vector<Edge> edges;
    vector<vector<int>> adj;
    int n;

public:
    FlowNetwork(int n) : n(n) {
        adj.resize(n);
    }

    // Add forward and matching backward residual edge
    void add_edge(int from, int to, int capacity) {
        // Forward edge
        adj[from].push_back(edges.size());
        edges.push_back({from, to, capacity, 0});
        // Backward edge (initial capacity 0)
        adj[to].push_back(edges.size());
        edges.push_back({to, from, 0, 0});
    }

    int size() const {
        return n;
    }

    // Returns the current residual capacity of an edge
    int residual_capacity(int id) const {
        return edges[id].capacity - edges[id].flow;
    }

    // Updates the flow along an edge and its dual backward edge
    void add_flow(int id, int flow) {
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow; // XOR with 1 finds the dual edge (0,1 or 2,3 etc)
    }

    const vector<int>& get_ids(int from) const {
        return adj[from];
    }

    const Edge& get_edge(int id) const {
        return edges[id];
    }
};

// Edmonds-Karp implementation
int max_flow(FlowNetwork& graph, int from, int to) {
    int flow = 0;

    while (true) {
        // BFS to find the shortest path in the residual graph
        vector<int> parent_edge(graph.size(), -1);
        queue<int> q;
        q.push(from);

        while (!q.empty() && parent_edge[to] == -1) {
            int curr = q.front();
            q.pop();

            for (int id : graph.get_ids(curr)) {
                int next = graph.get_edge(id).to;
                if (parent_edge[next] == -1 && next != from && graph.residual_capacity(id) > 0) {
                    parent_edge[next] = id;
                    q.push(next);
                }
            }
        }

        // If no path is found, we have reached max flow
        if (parent_edge[to] == -1) break;

        // Find the bottleneck capacity along the path
        int path_flow = 2e9; // Start with "infinity"
        for (int curr = to; curr != from; ) {
            int id = parent_edge[curr];
            path_flow = min(path_flow, graph.residual_capacity(id));
            curr = graph.get_edge(id).from;
        }

        // Update the residual graph
        for (int curr = to; curr != from; ) {
            int id = parent_edge[curr];
            graph.add_flow(id, path_flow);
            curr = graph.get_edge(id).from;
        }

        flow += path_flow;
    }

    return flow;
}

int main() {
    // Fast I/O for grading efficiency
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    FlowNetwork graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        // The problem uses 1-based indexing for cities
        graph.add_edge(u - 1, v - 1, c);
    }

    // Source is City 1 (index 0), Sink is City n (index n-1)
    cout << max_flow(graph, 0, n - 1) << "\n";

    return 0;
}
