/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 6
 * Assignment: Maximum Value of an Arithmetic Expression
 */

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long long eval(long long a, long long b, char op) {
    if (op == '*') return a * b;
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    return 0;
}

void get_min_max(int i, int j, vector<vector<long long>>& min_v, vector<vector<long long>>& max_v, const string& ops) {
    long long min_val = LLONG_MAX;
    long long max_val = LLONG_MIN;

    for (int k = i; k < j; k++) {
        char op = ops[k];
        long long a = eval(max_v[i][k], max_v[k + 1][j], op);
        long long b = eval(max_v[i][k], min_v[k + 1][j], op);
        long long c = eval(min_v[i][k], max_v[k + 1][j], op);
        long long d = eval(min_v[i][k], min_v[k + 1][j], op);

        min_val = min({min_val, a, b, c, d});
        max_val = max({max_val, a, b, c, d});
    }
    min_v[i][j] = min_val;
    max_v[i][j] = max_val;
}

long long get_maximum_value(const string &exp) {
    int n = (exp.length() + 1) / 2;
    vector<long long> digits(n);
    string ops = "";

    for (int i = 0; i < exp.length(); i++) {
        if (i % 2 == 0) digits[i / 2] = exp[i] - '0';
        else ops += exp[i];
    }

    vector<vector<long long>> min_v(n, vector<long long>(n, 0));
    vector<vector<long long>> max_v(n, vector<long long>(n, 0));

    // Base case: sub-expressions of length 1 (just the digits)
    for (int i = 0; i < n; i++) {
        min_v[i][i] = digits[i];
        max_v[i][i] = digits[i];
    }

    // Fill table diagonally
    for (int s = 1; s < n; s++) {
        for (int i = 0; i < n - s; i++) {
            int j = i + s;
            get_min_max(i, j, min_v, max_v, ops);
        }
    }

    return max_v[0][n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (cin >> s) {
        cout << get_maximum_value(s) << '\n';
    }
    return 0;
}
