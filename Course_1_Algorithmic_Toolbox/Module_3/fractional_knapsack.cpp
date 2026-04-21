/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Fractional Knapsack
 *
 * Problem Description:
 * Find the maximum value of items that fit into a knapsack of a given capacity.
 * Fractions of items can be taken. The optimal greedy strategy is to sort items 
 * by their value-to-weight ratio in descending order and fill the knapsack.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Create a structure to bind an item's value and weight together for easy sorting
struct Item {
    int value;
    int weight;
};

// Custom comparator to sort items by their value-to-weight ratio (descending)
bool compareItems(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double optimal_value = 0.0;
    int n = weights.size();
    
    // Bind the separate value and weight vectors into a single vector of Items
    vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        items[i].value = values[i];
        items[i].weight = weights[i];
    }

    // Sort the items using our custom comparator O(n log n)
    sort(items.begin(), items.end(), compareItems);

    // Greedily pick items
    for (int i = 0; i < n; i++) {
        // If the knapsack is full, stop iterating
        if (capacity == 0) {
            return optimal_value;
        }
        
        // Take the whole item if it fits, or the fractional remainder if it doesn't
        int take_weight = min(items[i].weight, capacity);
        
        // Add the value of the taken weight
        optimal_value += take_weight * ((double)items[i].value / items[i].weight);
        
        // Decrease the remaining capacity
        capacity -= take_weight;
    }

    return optimal_value;
}

int main() {
    // Fast I/O operations for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int capacity;
    
    if (cin >> n >> capacity) {
        vector<int> values(n);
        vector<int> weights(n);
        for (int i = 0; i < n; i++) {
            cin >> values[i] >> weights[i];
        }

        double optimal_value = get_optimal_value(capacity, weights, values);

        // Ensure the output prints with standard precision up to 4 decimal places
        cout << fixed << setprecision(4);
        cout << optimal_value << '\n';
    }
    
    return 0;
}
