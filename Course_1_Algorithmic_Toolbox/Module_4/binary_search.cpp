/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 4
 * Assignment: Binary Search
 *
 * Problem Explanation & Logic Breakdown:
 * The naive linear search checks every single element one by one (O(n) time). 
 * If you have a massive array and millions of queries, this will instantly 
 * trigger a "Time Limit Exceeded" error on the grader.
 * * Since the input array is already sorted, we can use a Divide and Conquer 
 * strategy. By checking the middle element, we can determine if our target 
 * is in the left half or the right half. We discard the other half and 
 * repeat. This cuts the search space in half every single step, dropping 
 * the time complexity to a lightning-fast O(log n).
 */

#include <iostream>
#include <vector>

using namespace std;

int binary_search_fast(const vector<int> &a, int x) {
    int left = 0;
    int right = (int)a.size() - 1; 
    
    while (left <= right) {
        // Calculate mid this way to prevent integer overflow for massive arrays
        int mid = left + (right - left) / 2;
        
        if (a[mid] == x) {
            return mid;       // Target found
        } else if (a[mid] < x) {
            left = mid + 1;   // Target is in the right half
        } else {
            right = mid - 1;  // Target is in the left half
        }
    }
    
    return -1; // Target not found
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        int m;
        cin >> m;
        vector<int> b(m);
        for (int i = 0; i < m; ++i) {
            cin >> b[i];
        }
        
        // Output the result using the fast binary search
        for (int i = 0; i < m; ++i) {
            cout << binary_search_fast(a, b[i]) << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
