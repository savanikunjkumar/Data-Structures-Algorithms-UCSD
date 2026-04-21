/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 6
 * Assignment: Partitioning 3
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int partition3(vector<int> &A) {
    int total_sum = accumulate(A.begin(), A.end(), 0);
    
    // If sum isn't divisible by 3, equal partition is impossible
    if (total_sum % 3 != 0 || A.size() < 3) {
        return 0;
    }

    int target = total_sum / 3;
    int n = A.size();

    // dp[s1][s2] stores whether it's possible to have two subsets with sums s1 and s2
    vector<vector<bool>> dp(target + 1, vector<bool>(target + 1, false));
    dp[0][0] = true;

    for (int x : A) {
        // Iterate backwards to ensure each element is only used once
        for (int s1 = target; s1 >= 0; --s1) {
            for (int s2 = target; s2 >= 0; --s2) {
                if (dp[s1][s2]) {
                    // Try adding x to the first subset
                    if (s1 + x <= target) {
                        dp[s1 + x][s2] = true;
                    }
                    // Try adding x to the second subset
                    if (s2 + x <= target) {
                        dp[s1][s2 + x] = true;
                    }
                }
            }
        }
    }

    // If we can fill two subsets to target, the third one is automatically target
    return dp[target][target] ? 1 : 0;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> A(n);
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }

        cout << partition3(A) << '\n';
    }

    return 0;
}
