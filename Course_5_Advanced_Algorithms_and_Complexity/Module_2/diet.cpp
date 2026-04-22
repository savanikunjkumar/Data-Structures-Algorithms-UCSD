/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 2 - Linear Programming
 * Assignment: Optimal Diet Problem
 *
 * Logic: Vertex Enumeration via Gaussian Elimination
 * Given the small constraints (n, m <= 8), we find all vertices of the 
 * feasible polyhedron by solving all possible subsets of m equations.
 * We include a bounding constraint (sum of x <= 10^9) to detect 
 * unbounded solutions (Infinity).
 *
 * Time Complexity: O(C(n+m, m) * m^3)
 * Space Complexity: O(n * m)
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double EPS = 1e-7;
const double BIG_NUMBER = 1e9;

typedef vector<double> Column;
typedef vector<Column> Matrix;

// Solve a system of m linear equations using Gaussian Elimination
int SolveEquation(Matrix a, Column b, Column& x) {
    int m = a.size();
    for (int i = 0; i < m; ++i) {
        int pivot = i;
        while (pivot < m && abs(a[pivot][i]) < EPS) pivot++;
        if (pivot == m) return 0; // Singular matrix
        swap(a[i], a[pivot]);
        swap(b[i], b[pivot]);

        double factor = a[i][i];
        for (int j = i; j < m; ++j) a[i][j] /= factor;
        b[i] /= factor;

        for (int k = 0; k < m; ++k) {
            if (k != i) {
                double mult = a[k][i];
                for (int j = i; j < m; ++j) a[k][j] -= mult * a[i][j];
                b[k] -= mult * b[i];
            }
        }
    }
    x = b;
    return 1;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    Matrix A(n, Column(m));
    Column b(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> A[i][j];
        cin >> b[i];
    }
    Column c(m);
    for (int i = 0; i < m; i++) cin >> c[i];

    // Add non-negativity constraints: -x_j <= 0
    for (int i = 0; i < m; i++) {
        Column row(m, 0.0);
        row[i] = -1.0;
        A.push_back(row);
        b.push_back(0.0);
    }
    
    // Add "Big-M" bounding constraint: sum(x_j) <= 10^9 + 7
    A.push_back(Column(m, 1.0));
    b.push_back(1e9 + 7);

    int total_constraints = A.size();
    double max_pleasure = -1e18;
    Column best_x(m);
    bool found_solution = false;
    bool is_infinite = false;

    // Iterate through all subsets of size m
    vector<int> subset(total_constraints);
    fill(subset.end() - m, subset.end(), 1);

    do {
        Matrix subA;
        Column subB;
        for (int i = 0; i < total_constraints; i++) {
            if (subset[i]) {
                subA.push_back(A[i]);
                subB.push_back(b[i]);
            }
        }

        Column x(m);
        if (SolveEquation(subA, subB, x)) {
            bool feasible = true;
            for (int i = 0; i < total_constraints; i++) {
                double lhs = 0;
                for (int j = 0; j < m; j++) lhs += A[i][j] * x[j];
                if (lhs > b[i] + EPS) {
                    feasible = false;
                    break;
                }
            }

            if (feasible) {
                double pleasure = 0;
                for (int i = 0; i < m; i++) pleasure += x[i] * c[i];
                if (pleasure > max_pleasure) {
                    max_pleasure = pleasure;
                    best_x = x;
                    found_solution = true;
                    
                    // Check if the solution is at the artificial boundary
                    double sum_x = 0;
                    for (double val : x) sum_x += val;
                    is_infinite = (sum_x > BIG_NUMBER);
                }
            }
        }
    } while (next_permutation(subset.begin(), subset.end()));

    if (!found_solution) {
        cout << "No solution" << endl;
    } else if (is_infinite) {
        cout << "Infinity" << endl;
    } else {
        cout << "Bounded solution" << endl;
        for (int i = 0; i < m; i++) {
            cout << fixed << setprecision(18) << best_x[i] << (i == m - 1 ? "" : " ");
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
