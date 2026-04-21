/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 5
 * Assignment: Edit Distance
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int edit_distance(const string &str1, const string &str2) {
    int n = str1.length();
    int m = str2.length();
    
    // dp[i][j] will store the edit distance of str1[0..i-1] and str2[0..j-1]
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    // Fill base cases for empty strings
    for (int i = 0; i <= n; ++i) dp[i][0] = i;
    for (int j = 0; j <= m; ++j) dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                // Characters match, no operation needed
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // Characters don't match, take min of insert, delete, or replace
                dp[i][j] = 1 + min({dp[i - 1][j],      // Deletion
                                   dp[i][j - 1],      // Insertion
                                   dp[i - 1][j - 1]}); // Substitution
            }
        }
    }

    return dp[n][m];
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str1, str2;
    if (cin >> str1 >> str2) {
        cout << edit_distance(str1, str2) << endl;
    }
    
    return 0;
}
