/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs (Course 3)
 * Module: Module 2 - Decomposition of Graphs 2
 * Assignment: Topological Sort
 *
 * Logic:
 * We use DFS to explore the graph. When a node's exploration is fully 
 * finished (post-order), we push it onto the 'order' vector. 
 * Reversing this vector gives the topological sort.
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// DFS helper to explore the graph and record post-order
void dfs(vector<vector<int>> &adj, vector<int> &used, vector<int> &order, int x) {
    used[x] = 1; // Mark current node as visited
    
    for (int neighbor : adj[x]) {
        if (!used[neighbor]) {
            // FIXED: Pass the 'used' vector as the second argument
            dfs(adj, used, order, neighbor);
        }
    }
    
    // Finished exploring x and all its dependencies
    order.push_back(x);
}

vector<int> toposort(vector<vector<int>> adj) {
    int n = adj.size();
    vector<int> used(n, 0);
    vector<int> order;

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(adj, used, order, i);
        }
    }

    // Reverse post-order to get topological order
    reverse(order.begin(), order.end());
    return order;
}

int main() {
    // Fast I/O is a must for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }

    vector<int> order = toposort(adj);
    
    for (size_t i = 0; i < order.size(); i++) {
        cout << order[i] + 1 << (i == order.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
