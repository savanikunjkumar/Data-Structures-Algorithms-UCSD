/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2 (Data Strycture) , Module 4 (Hash Tables)
 * Assignment:  matching with mismatches
 *
 * The Problem: Find occurrences of a pattern in a text with up to k mismatches.
 * * The Logic: We optimize the naive O(N*M) approach by combining Binary Search 
 * with Double Polynomial Prefix Hashing. For each window in the text, we binary 
 * search to find the longest common prefix (LCP) between the remaining pattern 
 * and text segment in O(log M) time. When we hit a mismatch, we jump over it, 
 * increment our mismatch counter, and binary search again. This skips large 
 * matching chunks instantly, dropping the total time complexity to O(N * k log M).
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solver {
    long long m1 = 1000000007;
    long long m2 = 1000000009;
    long long x = 263;

    vector<long long> h1_t, h2_t;
    vector<long long> h1_p, h2_p;
    vector<long long> x1_pow, x2_pow;

    void precompute_hashes(const string& str, vector<long long>& h1, vector<long long>& h2) {
        int n = str.length();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * x + str[i]) % m1;
            h2[i + 1] = (h2[i] * x + str[i]) % m2;
        }
    }

    // O(1) double hash verification
    bool check(int t_start, int p_start, int len) {
        if (len == 0) return true;
        
        long long hash1_t = (h1_t[t_start + len] - (h1_t[t_start] * x1_pow[len]) % m1 + m1) % m1;
        long long hash1_p = (h1_p[p_start + len] - (h1_p[p_start] * x1_pow[len]) % m1 + m1) % m1;
        
        if (hash1_t != hash1_p) return false;

        long long hash2_t = (h2_t[t_start + len] - (h2_t[t_start] * x2_pow[len]) % m2 + m2) % m2;
        long long hash2_p = (h2_p[p_start + len] - (h2_p[p_start] * x2_pow[len]) % m2 + m2) % m2;
        
        return hash2_t == hash2_p;
    }

    // Binary search for Longest Common Prefix (LCP) length
    int lcp(int t_start, int p_start, int max_len) {
        int left = 0, right = max_len;
        int match_len = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(t_start, p_start, mid)) {
                match_len = mid;
                left = mid + 1; // Try to find a longer match
            } else {
                right = mid - 1; // Match is shorter
            }
        }
        return match_len;
    }

public:
    Solver(const string& t, const string& p) {
        int max_len = max(t.length(), p.length());
        
        x1_pow.assign(max_len + 1, 1);
        x2_pow.assign(max_len + 1, 1);
        for (int i = 0; i < max_len; i++) {
            x1_pow[i + 1] = (x1_pow[i] * x) % m1;
            x2_pow[i + 1] = (x2_pow[i] * x) % m2;
        }

        precompute_hashes(t, h1_t, h2_t);
        precompute_hashes(p, h1_p, h2_p);
    }

    vector<int> solve(int k, const string& t, const string& p) {
        vector<int> pos;
        int t_len = t.length();
        int p_len = p.length();

        if (p_len > t_len) return pos;

        for (int i = 0; i <= t_len - p_len; i++) {
            int mismatches = 0;
            int curr_t = i;
            int curr_p = 0;

            // Jump through the strings using LCP
            while (mismatches <= k && curr_p < p_len) {
                int match_len = lcp(curr_t, curr_p, p_len - curr_p);
                
                curr_p += match_len;
                curr_t += match_len;

                // If we haven't reached the end of the pattern, it means we hit a mismatch
                if (curr_p < p_len) {
                    mismatches++;
                    curr_p++; // Skip the mismatched character
                    curr_t++;
                }
            }

            if (mismatches <= k) {
                pos.push_back(i);
            }
        }
        return pos;
    }
};

vector<int> solve(int k, const string &text, const string &pattern) {
    Solver solver(text, pattern);
    return solver.solve(k, text, pattern);
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int k;
    string t, p;
    while (cin >> k >> t >> p) {
        auto a = solve(k, t, p);
        cout << a.size();
        for (int x : a) {
            cout << " " << x;
        }
        cout << "\n";
    }
    
    return 0;
}
