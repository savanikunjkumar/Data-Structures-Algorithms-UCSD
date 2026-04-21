/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 2
 * Assignment: Merging Tables
 *
 * The Problem: Simulate merging database tables. When a source table merges into a 
 * destination table, the source is emptied and its rows are added to the destination. 
 * After each merge, print the maximum table size across all tables.
 * * The Logic: We use a Disjoint Set (Union-Find) data structure. To guarantee near O(1) 
 * time complexity per operation and prevent Time Limit Exceeded (TLE) errors, we implement 
 * two crucial heuristics: 
 * 1. Path Compression: In `getParent()`, we make every visited node point directly to the root.
 * 2. Union by Rank: In `merge()`, we always attach the shorter tree under the taller tree.
 * We also update the global `max_table_size` only when a valid merge occurs, ensuring O(1) tracking.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct DisjointSetsElement {
    int size, parent, rank;
    
    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
        size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
    int size;
    int max_table_size;
    vector<DisjointSetsElement> sets;

    DisjointSets(int size): size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }

    int getParent(int table) {
        // Find parent and compress path
        if (table != sets[table].parent) {
            // Recursively find the root and update the parent pointer of the current node
            sets[table].parent = getParent(sets[table].parent);
        }
        return sets[table].parent;
    }

    void merge(int destination, int source) {
        int realDestination = getParent(destination);
        int realSource = getParent(source);
        
        if (realDestination != realSource) {
            // Merge two components using the union by rank heuristic
            if (sets[realDestination].rank < sets[realSource].rank) {
                sets[realDestination].parent = realSource;
                sets[realSource].size += sets[realDestination].size;
                max_table_size = max(max_table_size, sets[realSource].size);
            } else {
                sets[realSource].parent = realDestination;
                sets[realDestination].size += sets[realSource].size;
                max_table_size = max(max_table_size, sets[realDestination].size);
                
                // If ranks are equal, the new root's rank increases by 1
                if (sets[realDestination].rank == sets[realSource].rank) {
                    sets[realDestination].rank++;
                }
            }
        }       
    }
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (cin >> n >> m) {
        DisjointSets tables(n);
        for (int i = 0; i < n; i++) {
            cin >> tables.sets[i].size;
            tables.max_table_size = max(tables.max_table_size, tables.sets[i].size);
        }

        for (int i = 0; i < m; i++) {
            int destination, source;
            cin >> destination >> source;
            --destination; // Convert to 0-based index
            --source;      // Convert to 0-based index
            
            tables.merge(destination, source);
            // Use \n instead of endl to prevent buffer flushing timeouts (TLE)
            cout << tables.max_table_size << "\n";
        }
    }

    return 0;
}
