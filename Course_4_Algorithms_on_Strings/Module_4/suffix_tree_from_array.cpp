/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 4 - Constructing Suffix Arrays And Suffix Trees 
* Assignment: Construct the Suffix Tree from the Suffix Array
 *
 * Logic: O(N) Tree Construction via LCP
 * We use the Suffix Array and LCP array to build the tree by walking up 
 * from the previous leaf. This version fixes the indexing errors regarding 
 * leaf node access and edge splitting.
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Node {
    int parent;
    map<char, int> children; 
    int depth;               
    int start;               
    int end;                 
};

vector<Node> tree;

void print_edges(int node) {
    for (auto const& [c, child] : tree[node].children) {
        cout << tree[child].start << " " << tree[child].end << "\n";
        print_edges(child);
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

    // Root node
    tree.push_back({-1, {}, 0, -1, -1});
    int curr = 0; 
    int lcp_prev = 0;

    for (int i = 0; i < n; i++) {
        int suffix = SA[i];
        
        while (tree[curr].depth > lcp_prev) {
            curr = tree[curr].parent;
        }

        if (tree[curr].depth == lcp_prev) {
            int leaf_idx = tree.size();
            tree.push_back({curr, {}, n - suffix, suffix + lcp_prev, n});
            tree[curr].children[text[suffix + lcp_prev]] = leaf_idx;
            curr = leaf_idx;
        } else {
            int edge_start = SA[i - 1] + tree[curr].depth;
            char edge_char = text[edge_start];
            int child = tree[curr].children[edge_char];
            
            int mid_idx = tree.size();
            tree.push_back({curr, {}, lcp_prev, tree[child].start, tree[child].start + lcp_prev - tree[curr].depth});
            
            tree[curr].children[text[tree[mid_idx].start]] = mid_idx;
            
            tree[child].parent = mid_idx;
            tree[child].start += lcp_prev - tree[curr].depth;
            tree[mid_idx].children[text[tree[child].start]] = child;
            
            int leaf_idx = tree.size();
            tree.push_back({mid_idx, {}, n - suffix, suffix + lcp_prev, n});
            tree[mid_idx].children[text[tree[leaf_idx].start]] = leaf_idx;
            curr = leaf_idx;
        }
        
        if (i < n - 1) {
            lcp_prev = LCP[i];
        }
    }

    cout << text << "\n";
    print_edges(0);

    return 0;
}
