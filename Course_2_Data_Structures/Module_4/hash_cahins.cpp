/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2 (Data Structures) , Module 4 (Hash Tables)
 * Assignment: Hashing with Chains
 *
 * The Problem: Implement a hash table using the chaining scheme to handle add, 
 * del, find, and check queries efficiently.
 * * The Logic: The naive starter code stores everything in a single vector and 
 * searches it linearly, resulting in O(N) time per query. We fix this by building 
 * a true Hash Table: a vector of linked lists (`vector<list<string>>`). The hash 
 * function maps a string to a specific bucket index. By using `push_front` to 
 * add new strings to a bucket's list, we keep the chain lengths short (average O(1) 
 * time complexity for all operations) and automatically satisfy the `check` query's 
 * requirement to print elements in reverse order of their insertion!
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    int bucket_count;
    // Hash table: an array of linked lists
    vector<list<string>> elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count): 
        bucket_count(bucket_count), 
        elems(bucket_count) {} // Initialize vector with bucket_count empty lists

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            // Because we used push_front(), the list is already in reverse insertion order
            for (const string& s : elems[query.ind]) {
                cout << s << " ";
            }
            cout << "\n";
        } else {
            size_t hash_val = hash_func(query.s);
            auto it = find(elems[hash_val].begin(), elems[hash_val].end(), query.s);

            if (query.type == "find") {
                writeSearchResult(it != elems[hash_val].end());
            } else if (query.type == "add") {
                // If not found, insert at the front of the list
                if (it == elems[hash_val].end()) {
                    elems[hash_val].push_front(query.s);
                }
            } else if (query.type == "del") {
                // If found, erase it from the list
                if (it != elems[hash_val].end()) {
                    elems[hash_val].erase(it);
                }
            }
        }
    }

    void processQueries() {
        int n;
        if (cin >> n) {
            for (int i = 0; i < n; ++i)
                processQuery(readQuery());
        }
    }
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int bucket_count;
    if (cin >> bucket_count) {
        QueryProcessor proc(bucket_count);
        proc.processQueries();
    }
    return 0;
}
