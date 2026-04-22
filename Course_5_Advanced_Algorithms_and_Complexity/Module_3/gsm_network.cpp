/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 3 - NP-Complete Problems
 * Assignment: Assign Frequencies to the Cells of a GSM Network
 *
 * Logic: Reduction to SAT (3-Coloring)
 * We map each vertex to 3 Boolean variables representing colors 1, 2, and 3.
 * 1. Each vertex must have at least one color: (x1 or x2 or x3).
 * 2. Adjacent vertices cannot have the same color: (not u_j or not v_j).
 *
 * Time Complexity: O(n + m) to generate the formula.
 * Space Complexity: O(n + m) to store edges and output.
 */

#include <iostream>
#include <vector>

using namespace std;

// Helper to map vertex and color to a unique SAT variable index
// Vertex i (1 to n), Color j (1 to 3) -> Index (1 to 3n)
inline int get_var(int vertex, int color) {
    return (vertex - 1) * 3 + color;
}

int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    struct Edge { int u, v; };
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v;
    }

    // Number of Variables: 3 per vertex
    int V = 3 * n;
    // Number of Clauses: n (at least one color) + 3*m (neighbor conflicts)
    int C = n + 3 * m;

    // Output number of clauses and variables
    cout << C << " " << V << "\n";

    // Clause Set 1: Each vertex i must have at least one color
    for (int i = 1; i <= n; ++i) {
        cout << get_var(i, 1) << " " << get_var(i, 2) << " " << get_var(i, 3) << " 0\n";
    }

    // Clause Set 2: Adjacent vertices must not share the same color
    for (const auto& edge : edges) {
        for (int color = 1; color <= 3; ++color) {
            // (not u has color 'color' OR not v has color 'color')
            cout << -get_var(edge.u, color) << " " << -get_var(edge.v, color) << " 0\n";
        }
    }

    return 0;
}
