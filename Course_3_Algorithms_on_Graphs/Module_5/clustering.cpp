/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Graphs by UC San Diego (Course 3)
 * Module: Module 5 - Minimum Spanning Trees
 * Assignment: Clustering
 *
 * Logic: Kruskal's Algorithm (Early Stopping)
 * We treat the points as a fully connected graph and sort all edges by weight.
 * We use a Disjoint Set Union (DSU) to merge the closest points into clusters.
 * We stop merging when we reach exactly 'k' clusters. The weight of the next 
 * valid edge that would merge two distinct clusters is the maximum spacing.
 *
 * Time Complexity: O(n^2 log n) due to sorting the edges.
 * Space Complexity: O(n^2) to store all edges.
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
    
    // Custom comparator to sort edges by weight ascending
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

double clustering(vector<int> x, vector<int> y, int k) {
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
    
    DisjointSet ds(n);
    int components = n; // Start with 'n' separate clusters
    
    // Process edges in increasing order of weight
    for (size_t i = 0; i < edges.size(); i++) {
        // If u and v belong to different clusters
        if (ds.find(edges[i].u) != ds.find(edges[i].v)) {
            // If we've already reached the target number of clusters,
            // this edge represents the shortest distance between two of them.
            if (components == k) {
                return edges[i].weight;
            }
            
            // Otherwise, merge them and decrease our cluster count
            ds.unite(edges[i].u, edges[i].v);
            components--;
        }
    }
    
    return -1.0;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n;
    int k;
    if (!(cin >> n)) return 0;
    
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    cin >> k;
    
    // Print with high precision as required by the grader
    cout << setprecision(10) << clustering(x, y, k) << "\n";
    
    return 0;
}
