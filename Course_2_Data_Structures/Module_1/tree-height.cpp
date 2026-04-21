/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Course - 2 , Module : 1 
 * Assignment: Compute Tree Height
 *
 * The Problem: Find the max depth of a tree given an array of parent pointers.
 * * The Logic: The naive starter code walks from every leaf up to the root, taking 
 * a brutally slow O(n^2) time. We fix this by finding the root (parent == -1) 
 * and using a Breadth-First Search (BFS) with a queue. This processes the tree 
 * level-by-level, finding the height in exactly O(n) time. Because BFS uses a 
 * heap-allocated queue instead of recursion, we can also completely delete all 
 * that messy OS-level stack-resizing code!
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Node> nodes(n);
    Node* root = NULL;

    // Build the tree and identify the root in a single pass O(n)
    for (int child_index = 0; child_index < n; child_index++) {
        int parent_index;
        cin >> parent_index;
        
        if (parent_index >= 0) {
            nodes[child_index].setParent(&nodes[parent_index]);
        } else {
            root = &nodes[child_index]; // Node with parent -1 is the root
        }
        nodes[child_index].key = child_index;
    }

    // Edge case: Empty tree
    if (root == NULL) {
        cout << 0 << "\n";
        return 0;
    }

    // Level-order traversal (BFS) to find the maximum height O(n)
    int maxHeight = 0;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int level_size = q.size();
        maxHeight++; // Moving down one level
        
        // Process all nodes at the current depth level
        for (int i = 0; i < level_size; i++) {
            Node* current = q.front();
            q.pop();
            
            // Queue up the next level of children
            for (Node* child : current->children) {
                q.push(child);
            }
        }
    }
    
    cout << maxHeight << "\n";
    return 0;
}
