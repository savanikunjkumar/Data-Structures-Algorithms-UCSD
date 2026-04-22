/*
 * Author: Kunjkumar Savani
 * Course: Advanced Algorithms & Complexity (Course 5)
 * Module: Module 2 - Linear Programming
 * Assignment: Infer Energy Values of Ingredients
 *
 * Logic: Gaussian Elimination with Partial Pivoting
 * We treat the menu items as a system of linear equations Ax = B.
 * Using partial pivoting ensures numerical stability, especially 
 * since the input can contain negative amounts or non-integers.
 *
 * Time Complexity: O(n^3)
 * Space Complexity: O(n^2)
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

typedef vector<double> Column;
typedef vector<Column> Matrix;

// Structure to hold the Augmented Matrix (A | B)
struct Equation {
    Matrix a;
    Column b;
};

Equation ReadEquation() {
    int n;
    cin >> n;
    Matrix a(n, Column(n));
    Column b(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
        cin >> b[i];
    }
    return {a, b};
}

Column SolveEquation(Equation equation) {
    Matrix &a = equation.a;
    Column &b = equation.b;
    int n = a.size();

    for (int step = 0; step < n; ++step) {
        // --- Partial Pivoting ---
        int pivot_row = step;
        for (int i = step + 1; i < n; ++i) {
            if (abs(a[i][step]) > abs(a[pivot_row][step])) {
                pivot_row = i;
            }
        }
        swap(a[step], a[pivot_row]);
        swap(b[step], b[pivot_row]);

        // Normalize the pivot row
        double factor = a[step][step];
        // If factor is effectively zero, the system might not have a unique solution.
        // Given the constraints, we assume a solution exists.
        if (abs(factor) > 1e-9) {
            for (int j = step; j < n; ++j) {
                a[step][j] /= factor;
            }
            b[step] /= factor;
        }

        // Eliminate other entries in the current column
        for (int i = 0; i < n; ++i) {
            if (i != step) {
                double multiplier = a[i][step];
                for (int j = step; j < n; ++j) {
                    a[i][j] -= multiplier * a[step][j];
                }
                b[i] -= multiplier * b[step];
            }
        }
    }

    return b;
}

void PrintColumn(const Column &column) {
    int n = column.size();
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; ++i) {
        cout << column[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Equation equation = ReadEquation();
    if (equation.a.empty()) return 0;
    
    Column result = SolveEquation(equation);
    PrintColumn(result);

    return 0;
}
