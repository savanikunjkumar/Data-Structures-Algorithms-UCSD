/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Largest Number
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Custom comparator: checks which concatenation forms a larger number
bool compare_strings(const string& a, const string& b) {
    return (a + b) > (b + a);
}

string largest_number(vector<string>& a) {
    // Sort the vector using our custom concatenation logic
    sort(a.begin(), a.end(), compare_strings);
    
    string result = "";
    for (size_t i = 0; i < a.size(); i++) {
        result += a[i];
    }
    
    return result;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<string> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        cout << largest_number(a) << "\n";
    }
    
    return 0;
}
