/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2 (Data Structure) , Module 4 (Hash Tables)
 * Assignment: Longest Common Substring
 *
 * The Problem: Find the longest common substring between two strings.
 * * The Logic: We optimize the naive O(N^3) approach by combining Binary Search 
 * with Double Polynomial Prefix Hashing. We binary search the target length 'L'. 
 * To verify if a common substring of length 'L' exists, we extract the double-hashes 
 * for all length 'L' substrings in 's', sort them, and binary search for the hashes 
 * of length 'L' substrings in 't'. Sorting the hashes avoids the heavy dynamic memory 
 * overhead and potential collision-attacks associated with std::unordered_map.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Answer {
    size_t i, j, len;
};

class Solver {
    long long m1 = 1000000007;
    long long m2 = 1000000009;
    long long x = 263;

    vector<long long> h1_s, h2_s;
    vector<long long> h1_t, h2_t;
    vector<long long> x1_pow, x2_pow;

    // Struct to hold combined hashes for easy sorting
    struct HashElement {
        unsigned long long hash;
        int index;

        bool operator<(const HashElement& other) const {
            return hash < other.hash;
        }
    };

    void precompute_hashes(const string& str, vector<long long>& h1, vector<long long>& h2) {
        int n = str.length();
        h1.assign(n + 1, 0);
        h2.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * x + str[i]) % m1;
            h2[i + 1] = (h2[i] * x + str[i]) % m2;
        }
    }

    pair<long long, long long> get_hash(const vector<long long>& h1, const vector<long long>& h2, int start, int len) {
        long long v1 = (h1[start + len] - (h1[start] * x1_pow[len]) % m1 + m1) % m1;
        long long v2 = (h2[start + len] - (h2[start] * x2_pow[len]) % m2 + m2) % m2;
        return {v1, v2};
    }

public:
    Solver(const string& s, const string& t) {
        int max_len = max(s.length(), t.length());
        
        x1_pow.assign(max_len + 1, 1);
        x2_pow.assign(max_len + 1, 1);
        for (int i = 0; i < max_len; i++) {
            x1_pow[i + 1] = (x1_pow[i] * x) % m1;
            x2_pow[i + 1] = (x2_pow[i] * x) % m2;
        }

        precompute_hashes(s, h1_s, h2_s);
        precompute_hashes(t, h1_t, h2_t);
    }

    // Checks if there's a common substring of exactly length 'len'
    Answer check(int len, const string& s, const string& t) {
        if (len == 0) return {0, 0, 0};

        vector<HashElement> s_hashes(s.size() - len + 1);
        for (int i = 0; i + len <= s.size(); i++) {
            auto h = get_hash(h1_s, h2_s, i, len);
            // Combine the two 32-bit hashes into one 64-bit integer
            unsigned long long merged = ((unsigned long long)h.first << 32) | h.second;
            s_hashes[i] = {merged, i};
        }

        // Sort to allow O(log N) binary search lookups (faster than map)
        sort(s_hashes.begin(), s_hashes.end());

        for (int j = 0; j + len <= t.size(); j++) {
            auto h = get_hash(h1_t, h2_t, j, len);
            unsigned long long merged = ((unsigned long long)h.first << 32) | h.second;
            
            // Binary search the hashes of 't' inside the sorted hashes of 's'
            int left = 0, right = s_hashes.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (s_hashes[mid].hash == merged) {
                    return {(size_t)s_hashes[mid].index, (size_t)j, (size_t)len};
                } else if (s_hashes[mid].hash < merged) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return {0, 0, 0}; // Not found
    }

    Answer solve(const string& s, const string& t) {
        int low = 1, high = min(s.size(), t.size());
        Answer best = {0, 0, 0};

        // Binary Search on the length of the substring
        while (low <= high) {
            int mid = low + (high - low) / 2;
            Answer res = check(mid, s, t);
            
            if (res.len > 0) {
                // If a match of length 'mid' is found, try to find a longer one
                best = res;
                low = mid + 1;
            } else {
                // Otherwise, the matching string must be shorter
                high = mid - 1;
            }
        }
        return best;
    }
};

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s, t;
    while (cin >> s >> t) {
        Solver solver(s, t);
        Answer ans = solver.solve(s, t);
        cout << ans.i << " " << ans.j << " " << ans.len << "\n";
    }
    
    return 0;
}
