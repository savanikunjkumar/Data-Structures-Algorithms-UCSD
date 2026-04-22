/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 4 - Coping with NP-Completeness
 * Assignment: School Bus (TSP with Bitmasking)
 *
 * Logic: Bellman-Held-Karp Algorithm
 * We use a DP table dp[mask][u] where 'mask' represents the set of visited 
 * vertices and 'u' is the last vertex visited. We iterate through all subsets 
 * of increasing size to build the solution.
 *
 * Time Complexity: O(n^2 * 2^n)
 * Space Complexity: O(n * 2^n)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e15; // Use a large value that won't overflow during addition

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Adjacency matrix initialization
    vector<vector<long long>> dist(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        // Problem uses 1-based indexing
        dist[u - 1][v - 1] = dist[v - 1][u - 1] = min(dist[u - 1][v - 1], t);
    }

    // dp[mask][u] stores {min_dist, parent_node}
    // Using a pair helps in path reconstruction
    vector<vector<pair<long long, int>>> dp(1 << n, vector<pair<long long, int>>(n, {INF, -1}));

    // Base case: Start at city 0
    dp[1][0] = {0, -1};

    // Iterate through all possible masks (subsets of vertices)
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)) || dp[mask][u].first == INF) continue;

            // Try moving to a city 'v' not yet in the mask
            for (int v = 0; v < n; v++) {
                if (!(mask & (1 << v))) {
                    int next_mask = mask | (1 << v);
                    long long new_dist = dp[mask][u].first + dist[u][v];
                    if (new_dist < dp[next_mask][v].first) {
                        dp[next_mask][v] = {new_dist, u};
                    }
                }
            }
        }
    }

    // Find the best way to return to city 0
    long long min_total_dist = INF;
    int last_node = -1;
    int full_mask = (1 << n) - 1;

    for (int i = 1; i < n; i++) {
        if (dp[full_mask][i].first + dist[i][0] < min_total_dist) {
            min_total_dist = dp[full_mask][i].first + dist[i][0];
            last_node = i;
        }
    }

    // Special case for n=2 (return trip is just the same edge twice)
    if (n == 2 && dist[0][1] != INF) {
        min_total_dist = dist[0][1] * 2;
        last_node = 1;
    }

    if (min_total_dist >= INF) {
        cout << -1 << endl;
    } else {
        cout << min_total_dist << endl;

        // Path reconstruction
        vector<int> path;
        int curr_mask = full_mask;
        int curr_node = last_node;

        while (curr_node != -1) {
            path.push_back(curr_node + 1);
            int prev_node = dp[curr_mask][curr_node].second;
            curr_mask ^= (1 << curr_node);
            curr_node = prev_node;
        }
        reverse(path.begin(), path.end());

        for (int i = 0; i < n; i++) {
            cout << path[i] << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}
