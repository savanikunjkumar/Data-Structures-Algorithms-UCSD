/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 1 - Flows in Networks
 * Assignment: Stock Charts (Advanced Problem)
 *
 * Logic: Minimum Path Cover in a DAG
 * 1. Build a DAG where an edge i -> j exists if stock i is strictly above stock j.
 * 2. Reduce the Minimum Path Cover problem to Bipartite Matching.
 * 3. Result = Total Stocks (n) - Max Matching Size.
 *
 * Time Complexity: O(n^2 * k + V * E^2)
 * Space Complexity: O(n^2)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Standard Edge structure for Max Flow
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
    int residual_capacity(int id) const { return edges[id].capacity - edges[id].flow; }
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

        int path_flow = 1e9;
        for (int curr = to; curr != from; ) {
            int id = parent_edge[curr];
            path_flow = min(path_flow, graph.residual_capacity(id));
            curr = graph.get_edge(id).from;
        }
        for (int curr = to; curr != from; ) {
            int id = parent_edge[curr];
            graph.add_flow(id, path_flow);
            curr = graph.get_edge(id).from;
        }
        flow += path_flow;
    }
    return flow;
}

bool is_above(const vector<int>& a, const vector<int>& b) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] <= b[i]) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<vector<int>> stocks(n, vector<int>(k));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> stocks[i][j];
        }
    }

    // Bipartite Graph Construction
    // Source: 0, Sink: 2n + 1
    // Left Set: 1 to n, Right Set: n + 1 to 2n
    FlowNetwork graph(2 * n + 2);
    int source = 0;
    int sink = 2 * n + 1;

    for (int i = 0; i < n; ++i) {
        graph.add_edge(source, i + 1, 1);
        graph.add_edge(n + i + 1, sink, 1);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            // If Stock i is strictly above Stock j at all points
            if (is_above(stocks[i], stocks[j])) {
                graph.add_edge(i + 1, n + j + 1, 1);
            }
        }
    }

    // Minimum Path Cover = n - Max Matching
    int matching_size = max_flow(graph, source, sink);
    cout << n - matching_size << "\n";

    return 0;
}
