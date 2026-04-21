/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 5
 * Assignment: Longest Common Subsequence of Two Sequences
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lcs2(vector<int> &a, vector<int> &b) {
    int n = a.size();
    int m = b.size();
    
    // dp[i][j] stores the LCS of a[0..i-1] and b[0..j-1]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                // If elements match, add 1 to the result of the previous subproblem
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                // If they don't match, take the maximum from the two possible directions
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[n][m];
}

int main() {
    // Fast I/O for grading limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int m;
        cin >> m;
        vector<int> b(m);
        for (int i = 0; i < m; i++) cin >> b[i];

        cout << lcs2(a, b) << "\n";
    }

    return 0;
}
