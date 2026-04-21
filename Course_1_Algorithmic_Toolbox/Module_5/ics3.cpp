/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 5
 * Assignment: Longest Common Subsequence of Three Sequences
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    int an = a.size();
    int bn = b.size();
    int cn = c.size();

    // 3D DP table: dp[i][j][k]
    // Initialized to 0
    vector<vector<vector<int>>> dp(an + 1, vector<vector<int>>(bn + 1, vector<int>(cn + 1, 0)));

    for (int i = 1; i <= an; i++) {
        for (int j = 1; j <= bn; j++) {
            for (int k = 1; k <= cn; k++) {
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
                    // Match in all three sequences
                    dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
                } else {
                    // No triple match, take the max of the three possible "previous" states
                    dp[i][j][k] = max({dp[i - 1][j][k], 
                                      dp[i][j - 1][k], 
                                      dp[i][j][k - 1]});
                }
            }
        }
    }

    return dp[an][bn][cn];
}

int main() {
    // Fast I/O for grading performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int an, bn, cn;

    if (cin >> an) {
        vector<int> a(an);
        for (int i = 0; i < an; i++) cin >> a[i];

        cin >> bn;
        vector<int> b(bn);
        for (int i = 0; i < bn; i++) cin >> b[i];

        cin >> cn;
        vector<int> c(cn);
        for (int i = 0; i < cn; i++) cin >> c[i];

        cout << lcs3(a, b, c) << "\n";
    }

    return 0;
}
