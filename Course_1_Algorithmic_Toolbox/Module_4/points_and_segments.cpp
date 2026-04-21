/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 4
 * Assignment: Organizing a Lottery (Points and Segments)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define event types to handle overlapping coordinates correctly
// Using -1 for start, 0 for point, and 1 for end ensures correct sorting
struct Event {
    int coord;
    int type; 
    int index; // To keep track of the original point order

    bool operator<(const Event& other) const {
        if (coord != other.coord) {
            return coord < other.coord;
        }
        return type < other.type;
    }
};

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<Event> events;
    vector<int> cnt(points.size());

    // Add segment starts
    for (int s : starts) {
        events.push_back({s, -1, 0});
    }
    // Add segment ends
    for (int e : ends) {
        events.push_back({e, 1, 0});
    }
    // Add points with their original index
    for (int i = 0; i < points.size(); i++) {
        events.push_back({points[i], 0, i});
    }

    // Sort all events O(N log N)
    sort(events.begin(), events.end());

    int open_segments = 0;
    for (const auto& e : events) {
        if (e.type == -1) {
            open_segments++; // Segment starts
        } else if (e.type == 1) {
            open_segments--; // Segment ends
        } else {
            cnt[e.index] = open_segments; // Store count for point at its original index
        }
    }

    return cnt;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (cin >> n >> m) {
        vector<int> starts(n), ends(n);
        for (int i = 0; i < n; i++) {
            cin >> starts[i] >> ends[i];
        }
        vector<int> points(m);
        for (int i = 0; i < m; i++) {
            cin >> points[i];
        }

        vector<int> cnt = fast_count_segments(starts, ends, points);
        
        for (int i = 0; i < cnt.size(); i++) {
            cout << cnt[i] << (i == cnt.size() - 1 ? "" : " ");
        }
        cout << '\n';
    }

    return 0;
}
