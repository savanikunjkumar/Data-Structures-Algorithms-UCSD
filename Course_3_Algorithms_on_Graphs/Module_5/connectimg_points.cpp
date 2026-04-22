/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 5 - Minimum Spanning Trees
 * Assignment: Building Roads to Connect Cities
 *
 * Logic: Kruskal's Algorithm with Disjoint Set Union (DSU)
 * 1. Compute the Euclidean distance between all pairs of points.
 * 2. Sort the edges by distance in ascending order.
 * 3. Use DSU to add edges to the MST, ensuring no cycles are formed, 
 * until all points are connected.
 *
 * Time Complexity: O(E log E) -> O(V^2 log V) since it's a complete graph.
 * Space Complexity: O(V^2) to store all possible edges.
 */

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Structure to represent an edge between two points
struct Edge {
    int u, v;
    double weight;
    
    // Custom comparator to sort edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Disjoint Set Union (DSU) with Path Compression and Union by Rank
struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    // Find with path compression
    int find(int i) {
        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }
        return parent[i];
    }
    
    // Union by rank
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j;
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }
};

double minimum_distance(vector<int> x, vector<int> y) {
    int n = x.size();
    vector<Edge> edges;
    
    // Generate all possible edges and calculate their Euclidean distances
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = sqrt(pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0));
            edges.push_back({i, j, dist});
        }
    }
    
    // Sort edges from shortest to longest
    sort(edges.begin(), edges.end());
    
    double result = 0.0;
    DisjointSet ds(n);
    
    // Process edges in increasing order of weight
    for (size_t i = 0; i < edges.size(); i++) {
        // If u and v belong to different sets, add the edge to the MST
        if (ds.find(edges[i].u) != ds.find(edges[i].v)) {
            result += edges[i].weight;
            ds.unite(edges[i].u, edges[i].v);
        }
    }
    
    return result;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n;
    if (!(cin >> n)) return 0;
    
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    
    // Output formatting required by the grader
    cout << setprecision(10) << minimum_distance(x, y) << "\n";
    
    return 0;
}
