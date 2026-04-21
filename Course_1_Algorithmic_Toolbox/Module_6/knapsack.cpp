/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 6
 * Assignment: Maximum Amount of Gold (Knapsack without Repetitions)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
    int n = w.size();
    
    // dp[i][j] is the max weight achieved with first i items and capacity j
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            // Default: don't include the current item
            dp[i][j] = dp[i - 1][j];
            
            // If the item fits, check if taking it gives a better result
            if (w[i - 1] <= j) {
                int val = dp[i - 1][j - w[i - 1]] + w[i - 1];
                if (dp[i][j] < val) {
                    dp[i][j] = val;
                }
            }
        }
    }

    return dp[n][W];
}

int main() {
    // Fast I/O for grading performance
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, W;
    if (cin >> W >> n) {
        vector<int> w(n);
        for (int i = 0; i < n; i++) {
            cin >> w[i];
        }

        cout << optimal_weight(W, w) << '\n';
    }

    return 0;
}
