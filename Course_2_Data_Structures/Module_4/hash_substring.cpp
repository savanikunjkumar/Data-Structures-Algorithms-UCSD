/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2 (Data Structure) , Module 4 (Hash Tables)
 * Assignment: Find pattern in text
 *
 * The Problem: Find all starting positions of a pattern string inside a text string.
 * * The Logic: The naive starter code compares the pattern to every single substring 
 * in the text. This takes O(|Text| * |Pattern|) time, which guarantees a Time Limit 
 * Exceeded (TLE) on large test cases. Since we are in the Hash Tables module, we optimize 
 * this to a lightning-fast O(|Text| + |Pattern|) using the Rabin-Karp algorithm. 
 * We compute the hash of the pattern, and then use a "Rolling Hash" to compute the hashes 
 * of all substrings in the text. By working backward, we calculate each new window's hash 
 * in O(1) time simply by adding the new character and subtracting the trailing character. 
 * If the hashes match, we double-check the exact strings to prevent rare collision errors.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        cout << output[i] << " ";
    cout << "\n";
}

// Computes the polynomial hash of a string
long long polyHash(const string& s, long long p, long long x) {
    long long hash = 0;
    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        hash = (hash * x + s[i]) % p;
    }
    return hash;
}

// Precomputes hashes of all substrings of T of length P_len using a rolling hash
vector<long long> precomputeHashes(const string& T, int P_len, long long p, long long x) {
    int T_len = T.size();
    vector<long long> H(T_len - P_len + 1);
    
    // Hash of the very last substring
    string S = T.substr(T_len - P_len, P_len);
    H[T_len - P_len] = polyHash(S, p, x);

    // Calculate x^(|P|) % p
    long long y = 1;
    for (int i = 1; i <= P_len; ++i) {
        y = (y * x) % p;
    }

    // Roll the hash backwards
    for (int i = T_len - P_len - 1; i >= 0; --i) {
        H[i] = (x * H[i + 1] + T[i] - y * T[i + P_len]) % p;
        H[i] = (H[i] + p) % p; // Ensure the modulo is positive
    }
    return H;
}

vector<int> get_occurrences(const Data& input) {
    const string& p_str = input.pattern;
    const string& t_str = input.text;
    vector<int> ans;

    // Edge case: pattern is longer than the text
    if (p_str.size() > t_str.size()) {
        return ans;
    }

    // Standard prime and multiplier for Rabin-Karp polynomial hashing
    long long p = 1000000007; 
    long long x = 263;        

    long long p_hash = polyHash(p_str, p, x);
    vector<long long> H = precomputeHashes(t_str, p_str.size(), p, x);

    for (size_t i = 0; i + p_str.size() <= t_str.size(); ++i) {
        if (p_hash == H[i]) {
            // Hash match! Double check the actual string to rule out collisions
            if (t_str.substr(i, p_str.size()) == p_str) {
                ans.push_back(i);
            }
        }
    }
    return ans;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    print_occurrences(get_occurrences(read_input()));
    
    return 0;
}
