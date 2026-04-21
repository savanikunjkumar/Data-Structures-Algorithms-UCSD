/*
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 6
 * Assignment: Binary Tree Traversals
 *
 * The Problem: Perform In-order, Pre-order, and Post-order traversals on a given binary tree.
 * * The Logic: The naive recursive approach can easily trigger a Stack Overflow (Runtime Error) 
 * on highly unbalanced trees (e.g., a straight line of 100,000 nodes). To prevent this without 
 * using messy OS-specific stack-resizing hacks, we use iteratively optimized traversals with 
 * `std::stack`. This guarantees O(N) time and strictly O(N) heap memory, safely passing all 
 * online grader limits. 
 * - In-order: Dive left, process root, dive right.
 * - Pre-order: Process root, push right child, push left child.
 * - Post-order: We use a clever trick—do a modified pre-order (Root -> Right -> Left), 
 * and then simply reverse the final array to get (Left -> Right -> Root)!
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class TreeOrders {
    int n;
    vector<int> key;
    vector<int> left;
    vector<int> right;

public:
    void read() {
        if (cin >> n) {
            key.resize(n);
            left.resize(n);
            right.resize(n);
            for (int i = 0; i < n; i++) {
                cin >> key[i] >> left[i] >> right[i];
            }
        }
    }

    vector<int> in_order() {
        vector<int> result;
        if (n == 0) return result;
        
        stack<int> s;
        int curr = 0;
        
        while (curr != -1 || !s.empty()) {
            // Reach the left most node of the current node
            while (curr != -1) {
                s.push(curr);
                curr = left[curr];
            }
            
            // Current must be -1 at this point
            curr = s.top();
            s.pop();
            
            result.push_back(key[curr]);
            
            // Visit the right subtree
            curr = right[curr];
        }
        return result;
    }

    vector<int> pre_order() {
        vector<int> result;
        if (n == 0) return result;
        
        stack<int> s;
        s.push(0);
        
        while (!s.empty()) {
            int curr = s.top();
            s.pop();
            result.push_back(key[curr]);
            
            // Push right child first so that left child is processed first (LIFO)
            if (right[curr] != -1) s.push(right[curr]);
            if (left[curr] != -1) s.push(left[curr]);
        }
        return result;
    }

    vector<int> post_order() {
        vector<int> result;
        if (n == 0) return result;
        
        stack<int> s;
        s.push(0);
        
        // Modified Pre-order: Root -> Right -> Left
        while (!s.empty()) {
            int curr = s.top();
            s.pop();
            result.push_back(key[curr]);
            
            // Push left first, so right is processed first
            if (left[curr] != -1) s.push(left[curr]);
            if (right[curr] != -1) s.push(right[curr]);
        }
        
        // Reverse the output to get the correct Post-order: Left -> Right -> Root
        reverse(result.begin(), result.end());
        return result;
    }
};

void print(vector<int> a) {
    for (size_t i = 0; i < a.size(); i++) {
        if (i > 0) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    TreeOrders t;
    t.read();
    
    // If the tree is empty, don't attempt to print
    if (t.in_order().empty()) return 0;

    print(t.in_order());
    print(t.pre_order());
    print(t.post_order());
    
    return 0;
}
