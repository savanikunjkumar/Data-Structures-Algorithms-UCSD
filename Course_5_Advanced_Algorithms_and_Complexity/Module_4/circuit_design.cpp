/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 4 - Coping with NP-Completeness
 * Assignment: Integrated Circuit Design (2-SAT)
 *
 * Logic: Implication Graph + Tarjan's SCC
 * 1. Construct an implication graph from 2-CNF clauses.
 * 2. Find SCCs using Tarjan's algorithm.
 * 3. Check for x and NOT x in the same SCC.
 * 4. Assign values based on the reverse topological order of SCCs.
 *
 * Time Complexity: O(V + C)
 * Space Complexity: O(V + C)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct TwoSAT {
    int n; // Number of variables
    vector<vector<int>> adj;
    vector<int> dfn, low, scc;
    vector<bool> in_stack;
    stack<int> st;
    int timer, scc_cnt;

    TwoSAT(int n) : n(n), adj(2 * n), dfn(2 * n, -1), low(2 * n, -1), 
                    scc(2 * n, -1), in_stack(2 * n, false), timer(0), scc_cnt(0) {}

    // Literal mapping: x_i -> 2*(i-1), NOT x_i -> 2*(i-1) + 1
    int literal(int i) {
        return i > 0 ? 2 * (i - 1) : 2 * (-i - 1) + 1;
    }

    int neg(int l) {
        return l ^ 1;
    }

    void add_clause(int i, int j) {
        int l1 = literal(i), l2 = literal(j);
        // (l1 OR l2) is equivalent to (NOT l1 => l2) AND (NOT l2 => l1)
        adj[neg(l1)].push_back(l2);
        adj[neg(l2)].push_back(l1);
    }

    void tarjan(int u) {
        dfn[u] = low[u] = timer++;
        st.push(u);
        in_stack[u] = true;

        for (int v : adj[u]) {
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            while (true) {
                int v = st.top();
                st.pop();
                in_stack[v] = false;
                scc[v] = scc_cnt;
                if (u == v) break;
            }
            scc_cnt++;
        }
    }

    void solve() {
        for (int i = 0; i < 2 * n; ++i) {
            if (dfn[i] == -1) tarjan(i);
        }

        vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            if (scc[2 * i] == scc[2 * i + 1]) {
                cout << "UNSATISFIABLE" << endl;
                return;
            }
            // In Tarjan's, SCC indices are in reverse topological order.
            // We assign TRUE to the literal that appears EARLIER in topological order 
            // (which means a HIGHER SCC index in Tarjan's logic).
            result[i] = (scc[2 * i] < scc[2 * i + 1] ? (i + 1) : -(i + 1));
        }

        cout << "SATISFIABLE" << endl;
        for (int i = 0; i < n; ++i) {
            cout << result[i] << (i == n - 1 ? "" : " ");
        }
        cout << endl;
    }
};

int main() {
    // Fast I/O is necessary for 1,000,000 variables
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int v, c;
    if (!(cin >> v >> c)) return 0;

    TwoSAT solver(v);
    for (int i = 0; i < c; ++i) {
        int l1, l2;
        cin >> l1 >> l2;
        solver.add_clause(l1, l2);
    }

    solver.solve();

    return 0;
}
