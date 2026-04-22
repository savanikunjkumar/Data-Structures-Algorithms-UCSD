/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 3 - Genome Assembly Faces Real Sequencing Data
 * Assignment: Finding a Circulation in a Network
 *
 * Logic: Reduction to Maximum Flow
 * We transform the circulation problem with lower bounds into a standard max flow 
 * problem by tracking the "demand" at each vertex caused by the lower bounds. 
 * We use Super Source and Super Sink nodes to balance these demands and run 
 * the Edmonds-Karp algorithm to find if a satisfying flow exists.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

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

    // Returns the index of the forward edge
    int add_edge(int from, int to, int capacity) {
        int forward_idx = edges.size();
        adj[from].push_back(forward_idx);
        edges.push_back({from, to, capacity, 0});
        
        adj[to].push_back(edges.size());
        edges.push_back({to, from, 0, 0});
        
        return forward_idx;
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

        int path_flow = 2e9;
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

struct OriginalEdge {
    int u, v, l, c;
    int forward_edge_id;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Node 0 is Super Source (S), Node n+1 is Super Sink (T)
    int S = 0;
    int T = n + 1;
    FlowNetwork graph(n + 2);

    vector<OriginalEdge> original_edges(m);
    vector<int> in_l(n + 1, 0);
    vector<int> out_l(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, l, c;
        cin >> u >> v >> l >> c;
        
        in_l[v] += l;
        out_l[u] += l;
        
        // Add edge to residual graph with capacity (c - l)
        int edge_id = graph.add_edge(u, v, c - l);
        original_edges[i] = {u, v, l, c, edge_id};
    }

    int total_demand = 0;

    // Balance the nodes with Super Source and Super Sink
    for (int i = 1; i <= n; ++i) {
        int M = in_l[i] - out_l[i];
        if (M > 0) {
            graph.add_edge(S, i, M);
            total_demand += M;
        } else if (M < 0) {
            graph.add_edge(i, T, -M);
        }
    }

    // Run Edmonds-Karp
    int resulting_flow = max_flow(graph, S, T);

    if (resulting_flow == total_demand) {
        cout << "YES\n";
        for (int i = 0; i < m; ++i) {
            // True flow = lower bound + extra flow found by max_flow
            int extra_flow = graph.get_edge(original_edges[i].forward_edge_id).flow;
            cout << original_edges[i].l + extra_flow << "\n";
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}
 
      
