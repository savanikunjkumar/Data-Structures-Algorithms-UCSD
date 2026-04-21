/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 6
 * Assignment: Is it a binary search tree ? 2
 *
 * The Problem: Determine if a given binary tree is a valid Binary Search Tree (BST).
 * * The Logic: We perform an iterative In-order traversal. In a valid BST, an in-order 
 * traversal guarantees the nodes are visited in strictly ascending numerical order. 
 * We use a stack to prevent Stack Overflow on deep trees, checking that every current 
 * node is strictly greater than the previously visited node in O(N) time.
 */

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

struct Node {
    int key;
    int left;
    int right;

    Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool IsBinarySearchTree(const vector<Node>& tree) {
    if (tree.empty()) {
        return true;
    }

    stack<int> s;
    int curr = 0; 
    
    // We use a long long to safely compare against INT_MIN node keys
    long long prev = LLONG_MIN; 

    while (curr != -1 || !s.empty()) {
        while (curr != -1) {
            s.push(curr);
            curr = tree[curr].left;
        }

        curr = s.top();
        s.pop();

        // In-order traversal MUST yield strictly increasing values
        if (tree[curr].key <= prev) {
            return false;
        }
        
        prev = tree[curr].key;
        curr = tree[curr].right;
    }

    return true;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes;
    if (cin >> nodes) {
        vector<Node> tree;
        for (int i = 0; i < nodes; ++i) {
            int key, left, right;
            cin >> key >> left >> right;
            tree.push_back(Node(key, left, right));
        }

        // The typo from the starter code has been fixed here with the extra ')'
        if (IsBinarySearchTree(tree)) {
            cout << "CORRECT\n";
        } else {
            cout << "INCORRECT\n";
        }
    }
    return 0;
}
