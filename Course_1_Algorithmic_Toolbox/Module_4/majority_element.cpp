/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 4
 * Assignment: Majority Element
 */

#include <iostream>
#include <vector>

using namespace std;

int get_majority_element(vector<int> &a, int left, int right) {
    // Base cases
    if (left == right) return -1;
    if (left + 1 == right) return a[left];

    // Divide
    int mid = left + (right - left) / 2;
    int left_candidate = get_majority_element(a, left, mid);
    int right_candidate = get_majority_element(a, mid, right);

    // If both halves agree on the majority element, return it
    if (left_candidate == right_candidate) {
        return left_candidate;
    }

    // Otherwise, count the occurrences of both candidates in the current range
    int left_count = 0;
    int right_count = 0;
    
    for (int i = left; i < right; ++i) {
        if (left_candidate != -1 && a[i] == left_candidate) {
            left_count++;
        }
        if (right_candidate != -1 && a[i] == right_candidate) {
            right_count++;
        }
    }

    // Check if either candidate strictly exceeds half
    int half_size = (right - left) / 2;
    if (left_count > half_size) return left_candidate;
    if (right_count > half_size) return right_candidate;

    return -1;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        // Output 1 if a majority element exists, otherwise 0
        cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
    }
    
    return 0;
}
