/*
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 1 - Suffix Trees
 * Assignment: Construct a Trie from a Collection of Patterns
 *
 * Logic:
 * We iteratively build the trie pattern by pattern. For each character
 * in a pattern, we check if the current node has an outgoing edge for 
 * that character. If it does, we traverse it. If not, we create a new 
 * node and map the edge.
 *
 * Time Complexity: O(|Patterns|) where |Patterns| is the total length of all strings.
 * Space Complexity: O(|Patterns|) to store the nodes and edges.
 */

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// We define a Trie as a vector of maps.
// The vector index is the node ID.
// The map stores pairs of <character_on_edge, destination_node_id>.
typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
    trie t;
    // Add the root node (node 0)
    t.push_back(edges());
    int new_node = 0;

    for (const string& pattern : patterns) {
        int current_node = 0; // Always start at the root for a new pattern
        
        for (char current_symbol : pattern) {
            // If there's an existing edge with the current symbol, follow it
            if (t[current_node].count(current_symbol)) {
                current_node = t[current_node][current_symbol];
            } 
            // Otherwise, create a new node and a new edge
            else {
                new_node++;
                t.push_back(edges()); // Allocate space for the new node
                t[current_node][current_symbol] = new_node; // Map the edge
                current_node = new_node; // Move to the new node
            }
        }
    }
    return t;
}

int main() {
    // Fast I/O is essential since the C++ time limit is a strict 0.5 seconds
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n;
    if (!(cin >> n)) return 0;
    
    vector<string> patterns(n);
    for (size_t i = 0; i < n; i++) {
        cin >> patterns[i];
    }

    trie t = build_trie(patterns);
    
    // Output the adjacency list in the required format: u->v:c
    for (size_t i = 0; i < t.size(); ++i) {
        for (const auto & edge : t[i]) {
            cout << i << "->" << edge.second << ":" << edge.first << "\n";
        }
    }

    return 0;
}
