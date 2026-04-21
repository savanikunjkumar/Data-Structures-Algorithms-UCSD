/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2 (Data Structure), Module 4 (Hash Tables)
 * Assignment: Phone Book
 *
 * The Problem: Implement a phone book manager that can add, delete, and find 
 * contacts. Phone numbers are guaranteed to be no longer than 7 digits.
 * * The Logic: The naive starter code uses a vector to store queries and searches 
 * through it sequentially. This means every single query takes O(N) time, leading 
 * to an O(N^2) total time complexity and a guaranteed Time Limit Exceeded (TLE). 
 * Because the maximum phone number is 9,999,999, we can completely eliminate 
 * search time by using Direct Addressing (a simplified Hash Table). We simply 
 * create an array of 10,000,000 strings where the index is the phone number itself. 
 * This drops the time complexity of add, delete, and find operations to absolute O(1)!
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    if (!(cin >> n)) return {};
    
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add") {
            cin >> queries[i].number >> queries[i].name;
        } else {
            cin >> queries[i].number;
        }
    }
    return queries;
}

void process_queries(const vector<Query>& queries) {
    // Direct Addressing array: size 10^7 covers all possible 7-digit numbers.
    // Initialized with empty strings to represent "not found" states.
    vector<string> contacts(10000000, ""); 
    
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "add") {
            // Index directly into the array using the phone number O(1)
            contacts[queries[i].number] = queries[i].name;
            
        } else if (queries[i].type == "del") {
            // Delete by resetting the string at that index O(1)
            contacts[queries[i].number] = "";
            
        } else { // "find" query
            // Retrieve directly via index O(1)
            if (contacts[queries[i].number] == "") {
                cout << "not found\n";
            } else {
                cout << contacts[queries[i].number] << "\n";
            }
        }
    }
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<Query> queries = read_queries();
    process_queries(queries);
    
    return 0;
}
