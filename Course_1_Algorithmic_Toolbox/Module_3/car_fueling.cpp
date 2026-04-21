/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Car Fueling
 */

#include <iostream>
#include <vector>

using namespace std;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    // Insert start (0) and destination (dist) to make the loop logic seamless
    stops.insert(stops.begin(), 0);
    stops.push_back(dist);

    int num_refills = 0;
    int current_refill = 0;
    int n = stops.size() - 2; // Number of actual intermediate stops

    while (current_refill <= n) {
        int last_refill = current_refill;
        
        // Greedily move to the furthest reachable stop
        while (current_refill <= n && stops[current_refill + 1] - stops[last_refill] <= tank) {
            current_refill++;
        }

        // If we didn't move forward at all, the gap is too large to cross
        if (current_refill == last_refill) {
            return -1;
        }

        // If we haven't reached the final destination yet, increment refill count
        if (current_refill <= n) {
            num_refills++;
        }
    }

    return num_refills;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d, m, n;
    if (cin >> d >> m >> n) {
        vector<int> stops(n);
        for (int i = 0; i < n; ++i) {
            cin >> stops[i];
        }

        cout << compute_min_refills(d, m, stops) << "\n";
    }

    return 0;
}
