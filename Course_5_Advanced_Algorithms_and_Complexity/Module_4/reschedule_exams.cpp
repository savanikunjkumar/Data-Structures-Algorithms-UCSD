/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 4 - Coping with NP-Completeness
 * Assignment: Reschedule the Exams (2-SAT Reduction)
 *
 * Logic:
 * Each student has exactly 2 new possible colors. We represent this binary 
 * choice with a 2-SAT variable. Friendships impose constraints on these 
 * choices. We solve the resulting 2-SAT using Tarjan's SCC algorithm.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

struct TwoSAT {
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, low, scc;
    vector<bool> in_stack;
    stack<int> st;
    int timer, scc_cnt;

    TwoSAT(int n) : n(n), adj(2 * n), dfn(2 * n, -1), low(2 * n, -1), 
                    scc(2 * n, -1), in_stack(2 * n, false), timer(0), scc_cnt(0) {}

    void add_clause(int u, bool val_u, int v, bool val_v) {
        // (u is val_u OR v is val_v)
        int l1 = 2 * u + (val_u ? 0 : 1);
        int l2 = 2 * v + (val_v ? 0 : 1);
        adj[l1 ^ 1].push_back(l2);
        adj[l2 ^ 1].push_back(l1);
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

    pair<bool, vector<int>> solve() {
        for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
        vector<int> assignment(n);
        for (int i = 0; i < n; ++i) {
            if (scc[2 * i] == scc[2 * i + 1]) return {false, {}};
            assignment[i] = (scc[2 * i] < scc[2 * i + 1]);
        }
        return {true, assignment};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    string current_colors;
    cin >> current_colors;

    // Determine available colors for each student
    vector<string> options(n);
    for (int i = 0; i < n; i++) {
        if (current_colors[i] == 'R') options[i] = "GB";
        else if (current_colors[i] == 'G') options[i] = "RB";
        else options[i] = "RG";
    }

    TwoSAT solver(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // 0-based

        // Check all 4 combinations of the 2 available colors for friends u and v
        for (int val_u = 0; val_u < 2; val_u++) {
            for (int val_v = 0; val_v < 2; val_v++) {
                if (options[u][val_u] == options[v][val_v]) {
                    // Forbid this combination: (x_u != val_u OR x_v != val_v)
                    solver.add_clause(u, val_u == 0, v, val_v == 0);
                }
            }
        }
    }

    auto result = solver.solve();
    if (!result.first) {
        cout << "Impossible" << endl;
    } else {
        string output = "";
        for (int i = 0; i < n; i++) {
            output += options[i][result.second[i]];
        }
        cout << output << endl;
    }

    return 0;
}
