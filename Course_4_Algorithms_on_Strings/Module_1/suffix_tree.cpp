/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 1 - Suffix Trees
 * Assignment: Construct the Suffix Tree of a String
 *
 * Logic: O(N^2) Direct Suffix Insertion
 * We iteratively insert every suffix into the tree. We traverse existing 
 * edges as far as they match. Upon a mismatch in the middle of an edge, 
 * we split the edge by inserting a new mid-node, branching off the remainder 
 * of the old edge and the new suffix. We store (start, end) indices on edges 
 * to save memory.
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Represents a compressed edge in the Suffix Tree
struct Edge {
    int start;
    int end; // Exclusive boundary: [start, end)
    int next_node;
};

// Represents a node which holds outgoing edges mapped by their first character
struct Node {
    map<char, Edge> edges;
};

// Function to build the Suffix Tree
vector<Node> build_suffix_tree(const string& text) {
    int N = text.length();
    vector<Node> tree;
    
    // Pre-allocate memory to prevent costly vector reallocations
    tree.reserve(2 * N);
    
    // Initialize the root node
    tree.push_back(Node());

    // Insert each suffix one by one
    for (int i = 0; i < N; i++) {
        int curr_node = 0;
        int curr_suffix_start = i;

        while (curr_suffix_start < N) {
            char c = text[curr_suffix_start];

            // If there's no outgoing edge starting with this character, create a new leaf
            if (tree[curr_node].edges.find(c) == tree[curr_node].edges.end()) {
                int leaf_node_idx = tree.size();
                tree.push_back(Node());
                
                tree[curr_node].edges[c] = {curr_suffix_start, N, leaf_node_idx};
                break; // Done inserting this suffix
            } 
            else {
                // An edge exists, trace it to see how much matches
                Edge current_edge = tree[curr_node].edges[c]; 
                int edge_len = current_edge.end - current_edge.start;
                int match_len = 0;

                while (match_len < edge_len && curr_suffix_start + match_len < N && 
                       text[current_edge.start + match_len] == text[curr_suffix_start + match_len]) {
                    match_len++;
                }

                // Case 1: We consumed the entire edge. Move to the next node.
                if (match_len == edge_len) {
                    curr_node = current_edge.next_node;
                    curr_suffix_start += match_len;
                } 
                // Case 2: Mismatch in the middle of the edge. We must SPLIT it.
                else {
                    // Create the intermediate branching node
                    int mid_node_idx = tree.size();
                    tree.push_back(Node());
                    
                    // Create the new leaf node for the remainder of the current suffix
                    int leaf_node_idx = tree.size();
                    tree.push_back(Node());

                    // Branch 1 from mid_node: The remainder of the old edge
                    char old_char = text[current_edge.start + match_len];
                    tree[mid_node_idx].edges[old_char] = {
                        current_edge.start + match_len, 
                        current_edge.end, 
                        current_edge.next_node
                    };

                    // Branch 2 from mid_node: The remainder of the newly inserted suffix
                    char new_char = text[curr_suffix_start + match_len];
                    tree[mid_node_idx].edges[new_char] = {
                        curr_suffix_start + match_len, 
                        N, 
                        leaf_node_idx
                    };

                    // Update the original edge from curr_node to point to mid_node and shorten it
                    tree[curr_node].edges[c].end = current_edge.start + match_len;
                    tree[curr_node].edges[c].next_node = mid_node_idx;

                    break; // Done inserting this suffix
                }
            }
        }
    }
    return tree;
}

int main() {
    // Fast I/O optimization
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (!(cin >> text)) return 0;

    vector<Node> tree = build_suffix_tree(text);

    // DFS to print all edge labels in the tree
    for (const auto& node : tree) {
        for (const auto& pair : node.edges) {
            const Edge& edge = pair.second;
            cout << text.substr(edge.start, edge.end - edge.start) << "\n";
        }
    }

    return 0;
}
