/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 5
 * Assignment: Money Change Again (Dynamic Programming)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_change(int m) {
    // min_coins[i] will store the minimum coins needed for amount i
    vector<int> min_coins(m + 1, 0);
    int coins[] = {1, 3, 4};

    for (int i = 1; i <= m; i++) {
        // Initialize with a large value (infinity)
        min_coins[i] = 1e9; 
        
        for (int coin : coins) {
            if (i >= coin) {
                int num_coins = min_coins[i - coin] + 1;
                if (num_coins < min_coins[i]) {
                    min_coins[i] = num_coins;
                }
            }
        }
    }

    return min_coins[m];
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    if (cin >> m) {
        cout << get_change(m) << '\n';
    }

    return 0;
}
