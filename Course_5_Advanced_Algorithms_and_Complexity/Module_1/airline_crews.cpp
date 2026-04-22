/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 1 - Flows in Networks
 * Assignment: Assigning Airline Crews to Flights
 *
 * Logic: Maximum Bipartite Matching via Edmonds-Karp
 * We construct a flow network where the source connects to all flights, 
 * and all crews connect to the sink. Edges exist between compatible 
 * flights and crews. All capacities are 1. The resulting max flow 
 * provides the maximum possible assignments.
 *
 * Time Complexity: O(V * E^2)
 * Space Complexity: O(V + E)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, capacity, flow;
};

class FlowNetwork {
    vector<Edge> edges;
    vector<vector<int>> adj;
    int n;

public:
    FlowNetwork(int n) : n(n) {
        adj.resize(n);
    }

    void add_edge(int from, int to, int capacity) {
        adj[from].push_back(edges.size());
        edges.push_back({from, to, capacity, 0});
        adj[to].push_back(edges.size());
        edges.push_back({to, from, 0, 0});
    }

    int size() const { return n; }

    int residual_capacity(int id) const {
        return edges[id].capacity - edges[id].flow;
    }

    void add_flow(int id, int flow) {
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }

    const vector<int>& get_ids(int from) const { return adj[from]; }
    const Edge& get_edge(int id) const { return edges[id]; }
};

int max_flow(FlowNetwork& graph, int from, int to) {
    int flow = 0;
    while (true) {
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

        if (parent_edge[to] == -1) break;

        int path_flow = 1; // Since all capacities are 1 in this bipartite matching
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Node indexing:
    // Source: 0
    // Flights: 1 to n
    // Crews: n+1 to n+m
    // Sink: n+m+1
    int source = 0;
    int sink = n + m + 1;
    FlowNetwork graph(n + m + 2);

    for (int i = 0; i < n; ++i) {
        graph.add_edge(source, i + 1, 1); // Source to Flight
        for (int j = 0; j < m; ++j) {
            int bit;
            cin >> bit;
            if (bit == 1) {
                graph.add_edge(i + 1, n + j + 1, 1); // Flight to Crew
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        graph.add_edge(n + j + 1, sink, 1); // Crew to Sink
    }

    max_flow(graph, source, sink);

    // Extraction: For each flight i, check outgoing edges to see which crew is assigned
    for (int i = 0; i < n; ++i) {
        int assigned_crew = -1;
        for (int id : graph.get_ids(i + 1)) {
            const Edge& e = graph.get_edge(id);
            // Check if the edge goes to a crew node and has flow
            if (e.to > n && e.to <= n + m && e.flow == 1) {
                assigned_crew = e.to - n; // Convert back to 1-based crew index
                break;
            }
        }
        cout << assigned_crew << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}
