/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 3
 * Assignment: Collecting Signatures (Covering Segments by Points)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Segment {
    int start, end;
};

// Custom comparator to sort segments by their end times
bool compareSegments(const Segment& a, const Segment& b) {
    return a.end < b.end;
}

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    
    // Step 1: Sort segments by end point
    sort(segments.begin(), segments.end(), compareSegments);
    
    // Step 2: Place the first point at the end of the first segment
    int current_point = segments[0].end;
    points.push_back(current_point);
    
    // Step 3: Iterate through the rest
    for (size_t i = 1; i < segments.size(); ++i) {
        // If the segment is not covered by our current point, we need a new one
        if (segments[i].start > current_point) {
            current_point = segments[i].end;
            points.push_back(current_point);
        }
    }
    
    return points;
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<Segment> segments(n);
        for (int i = 0; i < n; ++i) {
            cin >> segments[i].start >> segments[i].end;
        }
        
        vector<int> points = optimal_points(segments);
        
        cout << points.size() << "\n";
        for (size_t i = 0; i < points.size(); ++i) {
            cout << points[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
