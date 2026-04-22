/*
 * Author: Kunjkumar Savani
 * Logic: O(N) Suffix Tree Construction from SA and LCP
 * Fixes: 
 * 1. Replaced recursive DFS with iterative DFS to prevent SIGSEGV (Stack Overflow).
 * 2. Hardened the edge-splitting logic to prevent map insertion errors.
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

using namespace std;

struct Node {
    int parent;
    map<char, int> children;
    int string_depth; // Total characters from root to this node
    int start;        // Start index of the edge in Text
    int end;          // End index of the edge in Text (exclusive)
};

vector<Node> tree;

// Iterative DFS to prevent Stack Overflow (SIGSEGV)
void print_edges_iterative(int root) {
    // We use a stack to simulate the DFS
    // To maintain lexicographical order, we push children in reverse order
    stack<int> s;
    
    // We need to visit children of root in order. 
    // Since map is sorted, we iterate backwards and push to stack.
    auto it = tree[root].children.rbegin();
    while (it != tree[root].children.rend()) {
        s.push(it->second);
        it++;
    }

    while (!s.empty()) {
        int curr = s.top();
        s.pop();

        // Print the edge leading to this node
        cout << tree[curr].start << " " << tree[curr].end << "\n";

        // Push children in reverse order (to process smallest char first)
        auto child_it = tree[curr].children.rbegin();
        while (child_it != tree[curr].children.rend()) {
            s.push(child_it->second);
            child_it++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (!(cin >> text)) return 0;
    int n = text.length();

    vector<int> SA(n);
    for (int i = 0; i < n; i++) cin >> SA[i];

    vector<int> LCP(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> LCP[i];

    // Initialize root
    tree.reserve(2 * n); // Efficiency: pre-allocate memory
    tree.push_back({-1, {}, 0, -1, -1});
    
    int last_leaf = -1;

    for (int i = 0; i < n; i++) {
        int suffix = SA[i];
        int lcp_val = (i == 0) ? 0 : LCP[i - 1];
        
        int curr = (i == 0) ? 0 : last_leaf;

        // 1. Walk up until the node depth is <= LCP
        while (tree[curr].string_depth > lcp_val) {
            curr = tree[curr].parent;
        }

        if (tree[curr].string_depth == lcp_val) {
            // Case A: Just add a new leaf to the current node
            int leaf = tree.size();
            tree.push_back({curr, {}, n - suffix, suffix + lcp_val, n});
            tree[curr].children[text[tree[leaf].start]] = leaf;
            last_leaf = leaf;
        } else {
            // Case B: Must split an edge
            // Identify the edge to split
            int branch_char_pos = SA[i - 1] + tree[curr].string_depth;
            int child = tree[curr].children[text[branch_char_pos]];

            // Create mid node
            int mid = tree.size();
            int mid_start = tree[child].start;
            int mid_end = tree[child].start + (lcp_val - tree[curr].string_depth);
            
            tree.push_back({curr, {}, lcp_val, mid_start, mid_end});
            
            // Re-link: curr -> mid -> child
            tree[curr].children[text[mid_start]] = mid;
            tree[child].parent = mid;
            tree[child].start = mid_end;
            tree[mid].children[text[tree[child].start]] = child;

            // Add new leaf to mid
            int leaf = tree.size();
            tree.push_back({mid, {}, n - suffix, suffix + lcp_val, n});
            tree[mid].children[text[tree[leaf].start]] = leaf;
            last_leaf = leaf;
        }
    }

    cout << text << "\n";
    print_edges_iterative(0);

    return 0;
}

   
