/*
 * Author: Kunjkumar Savani
 * Course: Genome Assembly Programming Challenge (Course 6)
 * Module: Module 2 - Assembling Genomes Using De Bruijn Graphs
 * Assignment: Finding a k-Universal Circular String
 *
 * Logic: Eulerian Cycle on a De Bruijn Graph
 * We construct a graph where nodes are (k-1)-mers. Edges represent appending 
 * a 0 or a 1. Because the graph is strictly balanced (in-degree == out-degree == 2), 
 * we use Hierholzer's algorithm to find an Eulerian cycle. The bits appended 
 * during this cycle form our De Bruijn sequence.
 *
 * Time Complexity: O(2^k)
 * Space Complexity: O(2^k)
 */

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    if (!(cin >> k)) return 0;

    // Edge case for k=1 (though constraints say k >= 4)
    if (k == 1) {
        cout << "01\n";
        return 0;
    }

    // Number of vertices is 2^(k-1)
    int n = 1 << (k - 1);
    int mask = n - 1; // Used to keep values within k-1 bits

    // Construct the De Bruijn Graph
    // adj[u] will store the bits (0 or 1) that we can append
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        adj[i].push_back(1);
        adj[i].push_back(0);
    }

    // Hierholzer's Algorithm
    stack<int> st;
    st.push(0);
    vector<int> path;

    while (!st.empty()) {
        int u = st.top();
        
        if (!adj[u].empty()) {
            // Pick an edge (the bit to append)
            int bit = adj[u].back();
            adj[u].pop_back();
            
            // Calculate the next vertex: shift left, add bit, apply mask
            int v = ((u << 1) | bit) & mask;
            st.push(v);
        } else {
            // Backtrack
            path.push_back(u);
            st.pop();
        }
    }

    // The path is built backwards, so we reverse it
    reverse(path.begin(), path.end());

    // Reconstruct the string
    // We ignore the very first node and look at the transitions
    string result = "";
    for (size_t i = 1; i < path.size(); ++i) {
        // The appended bit is simply the LSB of the new vertex
        result += to_string(path[i] % 2);
    }

    cout << result << "\n";

    return 0;
}
