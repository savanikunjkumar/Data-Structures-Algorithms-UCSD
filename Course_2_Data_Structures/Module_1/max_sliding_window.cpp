/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 1
 * Assignment: Maximum in Sliding Window
 *
 * The Problem: Find the maximum value in every window of size w as it slides across an array.
 * * The Logic: The naive double-loop takes O(n*w) time, which is way too slow. We optimize 
 * this to a blazing fast O(n) using a Double-Ended Queue (deque). The deque stores the 
 * *indices* of elements, keeping them in strictly decreasing order of their values. As the 
 * window slides, we remove smaller elements from the back (they are useless now since the 
 * new element is bigger and will stay in the window longer) and drop elements from the 
 * front if they fall outside our current window. The front of the deque always instantly 
 * holds the maximum for the current window!
 */

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void max_sliding_window_fast(vector<int> const & A, int w) {
    deque<int> dq; // Stores indices of useful elements

    for (int i = 0; i < A.size(); ++i) {
        // 1. Remove the element at the front if it is no longer inside the current window
        if (!dq.empty() && dq.front() == i - w) {
            dq.pop_front();
        }

        // 2. Remove all elements from the back that are smaller than or equal to the current element.
        // They can never be the maximum because A[i] is larger and will stay in the window longer.
        while (!dq.empty() && A[dq.back()] <= A[i]) {
            dq.pop_back();
        }

        // 3. Add the current element's index to the back of the deque
        dq.push_back(i);

        // 4. Once we have processed at least 'w' elements, the front of the deque is our window's max
        if (i >= w - 1) {
            cout << A[dq.front()] << " ";
        }
    }
    cout << "\n";
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> A(n);
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
        }

        int w;
        cin >> w;

        max_sliding_window_fast(A, w);
    }

    return 0;
}
