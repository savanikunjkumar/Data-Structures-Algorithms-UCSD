/*
 * Author: Kunjkumar Savani
 * Course: Algorithms on Strings by UC San Diego (Course 4)
 * Module: Module 3 - Algorithmic Challenges
 * Assignment: Construct the Suffix Array of a Long String
 *
 * Logic: Prefix Doubling Algorithm O(N log N)
 * We sort cyclic shifts of the string by doubling the length of the sorted 
 * prefixes at each step (1, 2, 4, 8...). By assigning equivalence classes to 
 * each prefix and using Counting Sort on pairs of these classes, we avoid 
 * direct string comparisons entirely.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Convert alphabet to distinct integers for Counting Sort
int charToIndex(char c) {
    switch(c) {
        case '$': return 0;
        case 'A': return 1;
        case 'C': return 2;
        case 'G': return 3;
        case 'T': return 4;
        default: return 0;
    }
}

// Phase 1: Sort single characters using Counting Sort
vector<int> SortCharacters(const string& S) {
    int n = S.length();
    vector<int> order(n);
    vector<int> count(5, 0);
    
    for (int i = 0; i < n; i++) count[charToIndex(S[i])]++;
    for (int j = 1; j < 5; j++) count[j] += count[j - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        int c = charToIndex(S[i]);
        count[c]--;
        order[count[c]] = i;
    }
    return order;
}

// Assign equivalence classes to single characters
vector<int> ComputeCharClasses(const string& S, const vector<int>& order) {
    int n = S.length();
    vector<int> classes(n);
    classes[order[0]] = 0;
    
    for (int i = 1; i < n; i++) {
        if (S[order[i]] != S[order[i - 1]]) {
            classes[order[i]] = classes[order[i - 1]] + 1;
        } else {
            classes[order[i]] = classes[order[i - 1]];
        }
    }
    return classes;
}

// Phase 2: Sort strings of length 2L using Counting Sort on class pairs
vector<int> SortDoubled(const string& S, int L, const vector<int>& order, const vector<int>& classes) {
    int n = S.length();
    vector<int> count(n, 0);
    vector<int> newOrder(n);
    
    for (int i = 0; i < n; i++) count[classes[i]]++;
    for (int j = 1; j < n; j++) count[j] += count[j - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        // Find the start of the first half of the doubled string
        int start = (order[i] - L + n) % n;
        int cl = classes[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }
    return newOrder;
}

// Update equivalence classes for the newly sorted strings of length 2L
vector<int> UpdateClasses(const vector<int>& newOrder, const vector<int>& classes, int L) {
    int n = newOrder.size();
    vector<int> newClasses(n);
    newClasses[newOrder[0]] = 0;
    
    for (int i = 1; i < n; i++) {
        int cur = newOrder[i], prev = newOrder[i - 1];
        int mid = (cur + L) % n, midPrev = (prev + L) % n;
        
        if (classes[cur] != classes[prev] || classes[mid] != classes[midPrev]) {
            newClasses[cur] = newClasses[prev] + 1;
        } else {
            newClasses[cur] = newClasses[prev];
        }
    }
    return newClasses;
}

// Main Suffix Array Builder
vector<int> BuildSuffixArray(const string& S) {
    vector<int> order = SortCharacters(S);
    vector<int> classes = ComputeCharClasses(S, order);
    int L = 1;
    int n = S.length();
    
    // Keep doubling until the prefix length exceeds the string length
    while (L < n) {
        order = SortDoubled(S, L, order, classes);
        classes = UpdateClasses(order, classes, L);
        L *= 2;
    }
    return order;
}

int main() {
    // Fast I/O is absolutely essential here
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (cin >> text) {
        vector<int> suffix_array = BuildSuffixArray(text);
        
        for (int i = 0; i < suffix_array.size(); ++i) {
            cout << suffix_array[i] << (i == suffix_array.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    
    return 0;
}
