/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 3 - NP-Complete Problems
 * Assignment: Cleaning the Apartment (Hamiltonian Path to SAT)
 *
 * Logic:
 * We use n^2 variables where var(i, j) represents vertex i being at position j.
 * The constraints ensure the variables form a permutation matrix (each vertex 
 * exactly once, each position exactly once) and that adjacent positions in the 
 * permutation correspond to adjacent vertices in the original graph.
 *
 * Time Complexity: O(n^3) to generate the CNF formula.
 * Space Complexity: O(n^2) variables, ~100k literals.
 */

#include <iostream>
#include <vector>

using namespace std;

// Variable mapping: x_{i,j} -> (i-1)*n + j
// i: vertex index (1 to n), j: position index (1 to n)
inline int get_var(int i, int j, int n) {
    return (i - 1) * n + j;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // Use an adjacency matrix for O(1) edge lookups
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }

    vector<vector<int>> clauses;

    // 1. Each vertex appears in the path at least once
    for (int i = 1; i <= n; ++i) {
        vector<int> clause;
        for (int j = 1; j <= n; ++j) clause.push_back(get_var(i, j, n));
        clauses.push_back(clause);
    }

    // 2. Each vertex appears in the path at most once
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = j + 1; k <= n; ++k) {
                clauses.push_back({-get_var(i, j, n), -get_var(i, k, n)});
            }
        }
    }

    // 3. Each position in the path is occupied by at least one vertex
    for (int j = 1; j <= n; ++j) {
        vector<int> clause;
        for (int i = 1; i <= n; ++i) clause.push_back(get_var(i, j, n));
        clauses.push_back(clause);
    }

    // 4. Each position in the path is occupied by at most one vertex
    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= n; ++i) {
            for (int k = i + 1; k <= n; ++k) {
                clauses.push_back({-get_var(i, j, n), -get_var(k, j, n)});
            }
        }
    }

    // 5. If (i, k) is not an edge, vertex i and k cannot be neighbors in the path
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= n; ++k) {
            if (i != k && !adj[i][k]) {
                for (int j = 1; j < n; ++j) {
                    clauses.push_back({-get_var(i, j, n), -get_var(k, j + 1, n)});
                }
            }
        }
    }

    // Output number of clauses and number of variables
    cout << clauses.size() << " " << n * n << "\n";
    for (const auto& clause : clauses) {
        for (int lit : clause) {
            cout << lit << " ";
        }
        cout << "0\n";
    }

    return 0;
}
