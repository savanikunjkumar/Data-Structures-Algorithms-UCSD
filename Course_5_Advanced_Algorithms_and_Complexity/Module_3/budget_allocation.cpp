/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 3 - NP-Complete Problems
 * Assignment: Advertisement Budget Allocation (ILP to SAT)
 *
 * Logic: Forbidden Assignment Enumeration
 * Since each inequality has at most 3 variables, we can check all 2^k 
 * binary assignments for each constraint. Any assignment that violates 
 * the inequality is converted into a SAT clause that forbids that specific 
 * combination of values.
 *
 * Time Complexity: O(n * 2^k) where k=3
 * Space Complexity: O(n * m) to store the matrix
 */

#include <iostream>
#include <vector>

using namespace std;

struct Constraint {
    vector<pair<int, long long>> terms; // {variable_index, coefficient}
    long long b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // We store only non-zero coefficients to handle the "at most 3" property
    vector<Constraint> constraints(n);
    vector<vector<long long>> A(n, vector<long long>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> A[i][j];
            if (A[i][j] != 0) {
                constraints[i].terms.push_back({j + 1, A[i][j]});
            }
        }
    }
    for (int i = 0; i < n; ++i) cin >> constraints[i].b;

    vector<vector<int>> clauses;

    for (const auto& cnst : constraints) {
        int k = cnst.terms.size();
        // Try all 2^k binary combinations for the variables in this constraint
        for (int mask = 0; mask < (1 << k); ++mask) {
            long long current_sum = 0;
            for (int j = 0; j < k; ++j) {
                if ((mask >> j) & 1) {
                    current_sum += cnst.terms[j].second;
                }
            }

            // If the combination violates the inequality, create a blocking clause
            if (current_sum > cnst.b) {
                vector<int> clause;
                for (int j = 0; j < k; ++j) {
                    bool bit = (mask >> j) & 1;
                    // If bit is 1, we need (not x_j). If 0, we need (x_j).
                    clause.push_back(bit ? -cnst.terms[j].first : cnst.terms[j].first);
                }
                clauses.push_back(clause);
            }
        }
    }

    // Special Case: If no clauses were generated, the problem is always satisfiable.
    // We output a dummy clause that is always true (x1 or not x1).
    if (clauses.empty()) {
        cout << "1 1\n1 -1 0\n";
    } else {
        cout << clauses.size() << " " << m << "\n";
        for (const auto& clause : clauses) {
            for (int literal : clause) {
                cout << literal << " ";
            }
            cout << "0\n";
        }
    }

    return 0;
}
