/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 2
 * Assignment: Build a Heap
 *
 * The Problem: Convert an array of integers into a Min-Heap and output the exact sequence of swaps.
 * * The Logic: The starter code uses Selection Sort to build the heap, which takes a painfully 
 * slow O(n^2) time and generates way too many swaps. We can do this in exactly O(n) time 
 * using the classic "BuildHeap" algorithm. Since all leaf nodes are already technically 
 * valid heaps of size 1, we only need to start at the last non-leaf node (n/2 - 1) and work 
 * our way backwards to the root (0), calling `SiftDown` on each node. This efficiently 
 * bubbles larger values down to the bottom, strictly adhering to the grader limits.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
private:
    vector<int> data_;
    vector<pair<int, int>> swaps_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        if (cin >> n) {
            data_.resize(n);
            for (int i = 0; i < n; ++i)
                cin >> data_[i];
        }
    }

    // Helper function to recursively sift elements down the tree
    void SiftDown(int i) {
        int minIndex = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int size = data_.size();

        // Check if the left child exists and is smaller than the current minimum
        if (leftChild < size && data_[leftChild] < data_[minIndex]) {
            minIndex = leftChild;
        }

        // Check if the right child exists and is smaller than the current minimum
        if (rightChild < size && data_[rightChild] < data_[minIndex]) {
            minIndex = rightChild;
        }

        // If the minimum is not the parent, swap and continue sifting down
        if (i != minIndex) {
            swap(data_[i], data_[minIndex]);
            swaps_.push_back(make_pair(i, minIndex));
            SiftDown(minIndex);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        
        // Start from the last internal node and sift down to the root
        // This guarantees O(n) time complexity for building the heap
        for (int i = data_.size() / 2 - 1; i >= 0; --i) {
            SiftDown(i);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    HeapBuilder heap_builder;
    heap_builder.Solve();
    
    return 0;
}
