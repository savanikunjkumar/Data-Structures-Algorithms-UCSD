/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 1
 * Assignment: Stack with Max
 *
 * The Problem: Implement a stack that can return its maximum value instantly.
 * * The Logic: The starter code uses `max_element` to scan the entire stack every time 
 * you call `Max()`. This takes O(n) time and will fail the grader with a Time Limit 
 * Exceeded (TLE) error. To fix this, we use an auxiliary `max_stack`. Every time we 
 * push a value, we also push the *current maximum* onto `max_stack`. This means the 
 * top of `max_stack` always holds the maximum value for the current state of the main 
 * stack, dropping the time complexity of all operations down to a perfect O(1).
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

class StackWithMax {
    stack<int> main_stack;
    stack<int> max_stack;

public:
    void Push(int value) {
        main_stack.push(value);
        if (max_stack.empty() || value >= max_stack.top()) {
            max_stack.push(value);
        } else {
            max_stack.push(max_stack.top());
        }
    }

    void Pop() {
        if (!main_stack.empty()) {
            main_stack.pop();
            max_stack.pop();
        }
    }

    int Max() const {
        return max_stack.top();
    }
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int num_queries = 0;
    if (!(cin >> num_queries)) return 0;

    string query;
    int value;
    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(value);
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.Max() << "\n";
        }
    }
    
    return 0;
}
