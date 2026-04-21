/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Maximum Number of Prizes
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> optimal_summands(int n) {
    vector<int> summands;
    
    // Start trying to give out 1, then 2, then 3...
    for (int i = 1; i <= n; i++) {
        n -= i; // Subtract the current amount from our total
        
        // If the remaining amount isn't strictly greater than our current amount,
        // we can't continue the pattern. Just combine the rest with the current amount.
        if (n <= i) {
            summands.push_back(n + i);
            break;
        } else {
            summands.push_back(i);
        }
    }
    
    return summands;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> summands = optimal_summands(n);
        
        cout << summands.size() << '\n';
        for (size_t i = 0; i < summands.size(); ++i) {
            cout << summands[i] << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
