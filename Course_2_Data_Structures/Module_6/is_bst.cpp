/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 6
 * Assignment: Is it a binary search tree?
 *
 * The Problem: Determine if a given binary tree is a valid Binary Search Tree (BST).
 * * The Logic: The most elegant and efficient way to verify a BST is to perform an 
 * In-order traversal. In a mathematically valid BST, an in-order traversal guarantees 
 * that the nodes will be visited in strictly ascending numerical order. To avoid 
 * Stack Overflow (Runtime Error) on deeply skewed trees, we use an iterative stack 
 * approach instead of naive recursion. We simply keep track of the previously visited 
 * node's value (`prev`) and ensure every current node is strictly greater than it. 
 * This perfectly handles the validation in O(N) time and O(N) space.
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
    // An empty tree is technically a valid BST
    if (tree.empty()) {
        return true;
    }

    stack<int> s;
    int curr = 0; // Start at the root (index 0)
    
    // We use a long long to safely compare against INT_MIN node keys
    long long prev = LLONG_MIN; 

    while (curr != -1 || !s.empty()) {
        // Dive completely to the left
        while (curr != -1) {
            s.push(curr);
            curr = tree[curr].left;
        }

        // Process the current node
        curr = s.top();
        s.pop();

        // In-order traversal MUST yield strictly increasing values
        if (tree[curr].key <= prev) {
            return false;
        }
        
        // Update the previous value tracker
        prev = tree[curr].key;

        // Move to the right subtree
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

        // Note: Fixed the missing closing parenthesis from the starter code here
        if (IsBinarySearchTree(tree)) {
            cout << "CORRECT\n";
        } else {
            cout << "INCORRECT\n";
        }
    }
    return 0;
}
