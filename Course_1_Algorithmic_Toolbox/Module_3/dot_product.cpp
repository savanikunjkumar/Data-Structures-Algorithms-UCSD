/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Maximum Advertisement Revenue (Maximum Dot Product)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long max_dot_product(vector<int>& a, vector<int>& b) {
    // Sort both vectors to easily pair the largest elements together
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        // Cast to long long to prevent integer overflow during multiplication
        result += (long long)a[i] * b[i];
    }
    
    return result;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        cout << max_dot_product(a, b) << "\n";
    }
    
    return 0;
}
