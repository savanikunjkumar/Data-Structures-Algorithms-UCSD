/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 4 - Coping with NP-Completeness
 * Assignment: Plan a Fun Party (DP on Trees)
 *
 * Logic: Maximum Weight Independent Set on a Tree
 * We use two DP states for each node: 
 * dp_in[u]: Max fun factor if node u is included.
 * dp_out[u]: Max fun factor if node u is excluded.
 * The answer is max(dp_in[root], dp_out[root]).
 *
 * Time Complexity: O(N) - Every node and edge is visited once.
 * Space Complexity: O(N) - To store the tree and DP tables.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Adjacency list to represent the subordination tree
typedef vector<vector<int>> Graph;

// DP tables
// We use long long because the total fun factor can exceed 2^31 - 1
vector<long long> dp_in;
vector<long long> dp_out;
vector<int> fun_factors;

void dfs(int u, int p, const Graph& adj) {
    dp_in[u] = fun_factors[u];
    dp_out[u] = 0;

    for (int v : adj[u]) {
        if (v == p) continue; // Skip the parent to avoid cycles in the undirected input

        dfs(v, u, adj);

        // If we invite u, we cannot invite child v
        dp_in[u] += dp_out[v];

        // If we don't invite u, we take the best option for child v
        dp_out[u] += max(dp_in[v], dp_out[v]);
    }
}

int main() {
    // Fast I/O is helpful for N = 100,000
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    fun_factors.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> fun_factors[i];
    }

    Graph adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        // The problem uses 1-based indexing
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    dp_in.assign(n, 0);
    dp_out.assign(n, 0);

    // We can start the DFS from any node, let's pick 0 (CEO or any other)
    dfs(0, -1, adj);

    // The answer is the best we can do at the root
    cout << max(dp_in[0], dp_out[0]) << endl;

    return 0;
}
