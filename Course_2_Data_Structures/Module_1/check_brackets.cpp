/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 1
 * Assignment: Check Brackets in the Code
 *
 * The Problem: Check if brackets in a string are matched and nested correctly. 
 * If not, output the 1-based index of the first error.
 * * The Logic: We use a Stack. When we see an opening bracket, we push it onto 
 * the stack. When we see a closing bracket, we pop the top of the stack and 
 * check if they match. If they don't, or if the stack is already empty, we instantly 
 * print the current index. If we finish reading the string and the stack is 
 * NOT empty, the bottom-most element in the stack is our first unclosed 
 * opening bracket! This guarantees an optimal O(n) runtime.
 */

#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string text;
    if (!getline(cin, text)) return 0;

    stack<Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Push the opening bracket and its 1-based position
            opening_brackets_stack.push(Bracket(next, position + 1));
        }

        if (next == ')' || next == ']' || next == '}') {
            // If stack is empty, we have an unmatched closing bracket
            if (opening_brackets_stack.empty()) {
                cout << position + 1 << "\n";
                return 0;
            }

            Bracket top = opening_brackets_stack.top();
            opening_brackets_stack.pop();

            // If the closing bracket doesn't match the top opening bracket
            if (!top.Matchc(next)) {
                cout << position + 1 << "\n";
                return 0;
            }
        }
    }

    // Printing answer
    if (opening_brackets_stack.empty()) {
        cout << "Success\n";
    } else {
        // If the stack is not empty, there are unmatched opening brackets.
        // We need to print the 1-based index of the *first* unmatched opening bracket,
        // which is located at the very bottom of our stack.
        int first_unmatched_position = 0;
        while (!opening_brackets_stack.empty()) {
            first_unmatched_position = opening_brackets_stack.top().position;
            opening_brackets_stack.pop();
        }
        cout << first_unmatched_position << "\n";
    }

    return 0;
}
