/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2 (Data Structure) , Module 4 (Hash Tables)
 * Assignment: Substring Equality
 *
 * The Problem: Check if two substrings of length 'l' starting at indices 'a' and 'b' are identical.
 * * The Logic: The naive starter code uses `s.substr()`, which takes O(l) time per query. 
 * For 'q' queries, this runs in O(q * l) time and will definitely hit a Time Limit Exceeded (TLE).
 * We can optimize the query time to a blistering O(1) using Polynomial Prefix Hashing. 
 * By precomputing an array of hashes for all prefixes of the string, we can isolate the hash 
 * of any substring mathematically: Hash(a, l) = H[a+l] - H[a] * x^l. 
 * Because hash collisions can happen, we use "Double Hashing" (calculating hashes with two 
 * different prime numbers simultaneously). If both hashes match, we can be mathematically 
 * certain the strings are identical without ever checking the actual characters! 
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solver {
    string s;
    // Two large prime numbers to virtually eliminate collision risk
    long long m1 = 1000000007;
    long long m2 = 1000000009;
    long long x = 263;
    
    // Arrays to store prefix hashes and precomputed powers of x
    vector<long long> h1, h2;
    vector<long long> x1_pow, x2_pow;

public: 
    Solver(string s) : s(s) {   
        int n = s.length();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        
        x1_pow.assign(n + 1, 1);
        x2_pow.assign(n + 1, 1);

        // Precompute prefix hashes and powers in O(N) time
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * x + s[i]) % m1;
            h2[i + 1] = (h2[i] * x + s[i]) % m2;
            
            x1_pow[i + 1] = (x1_pow[i] * x) % m1;
            x2_pow[i + 1] = (x2_pow[i] * x) % m2;
        }
    }
    
    bool ask(int a, int b, int l) {
        // Extract the hash for the first substring in O(1) time
        long long hash1_a = (h1[a + l] - (h1[a] * x1_pow[l]) % m1 + m1) % m1;
        long long hash1_b = (h1[b + l] - (h1[b] * x1_pow[l]) % m1 + m1) % m1;
        
        // If the first hash doesn't match, they aren't equal
        if (hash1_a != hash1_b) {
            return false;
        }

        // Double check with the second hash to prevent collisions
        long long hash2_a = (h2[a + l] - (h2[a] * x2_pow[l]) % m2 + m2) % m2;
        long long hash2_b = (h2[b + l] - (h2[b] * x2_pow[l]) % m2 + m2) % m2;
        
        return hash2_a == hash2_b;
    }
};

int main() {
    // Fast I/O is crucial for processing massive numbers of queries
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    string s;
    int q;
    if (cin >> s >> q) {
        Solver solver(s);
        for (int i = 0; i < q; i++) {
            int a, b, l;
            cin >> a >> b >> l;
            cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
