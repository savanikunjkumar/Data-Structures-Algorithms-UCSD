/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 4
 * Assignment: Number of Inversions
 */

#include <iostream>
#include <vector>

using namespace std;

long long get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    
    // Base case: if the segment has 1 or fewer elements, it's already sorted
    if (right <= left + 1) {
        return number_of_inversions;
    }
    
    size_t mid = left + (right - left) / 2;
    
    // Divide and conquer
    number_of_inversions += get_number_of_inversions(a, b, left, mid);
    number_of_inversions += get_number_of_inversions(a, b, mid, right);
    
    // Merge step
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    
    while (i < mid && j < right) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
            // Since a[i] > a[j], a[j] is smaller than all remaining elements in the left half.
            number_of_inversions += (mid - i);
        }
    }
    
    // Copy remaining elements from left half, if any
    while (i < mid) {
        b[k++] = a[i++];
    }
    
    // Copy remaining elements from right half, if any
    while (j < right) {
        b[k++] = a[j++];
    }
    
    // Copy the sorted merged segment back into the original array
    for (i = left; i < right; i++) {
        a[i] = b[i];
    }
    
    return number_of_inversions;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (size_t i = 0; i < a.size(); i++) {
            cin >> a[i];
        }
        
        // b is used as a temporary buffer during the merge step
        vector<int> b(a.size());
        
        cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';
    }
    
    return 0;
}
