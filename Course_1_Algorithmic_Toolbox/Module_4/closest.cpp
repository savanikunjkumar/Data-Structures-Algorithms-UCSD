/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 4
 * Assignment: Closest Pair of Points
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;
};

// Standard Euclidean distance formula
double dist(Point p1, Point p2) {
    return sqrt(pow((double)p1.x - p2.x, 2) + pow((double)p1.y - p2.y, 2));
}

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double find_minimal_distance(vector<Point>& pts, int left, int right) {
    // Base case: small number of points can be solved naively
    if (right - left <= 3) {
        double min_d = 1e18; // Infinity
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                min_d = min(min_d, dist(pts[i], pts[j]));
            }
        }
        return min_d;
    }

    int mid = left + (right - left) / 2;
    int mid_x = pts[mid].x;

    // Divide and Conquer
    double d = min(find_minimal_distance(pts, left, mid), 
                   find_minimal_distance(pts, mid, right));

    // Check the strip crossing the dividing line
    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(pts[i].x - mid_x) < d) {
            strip.push_back(pts[i]);
        }
    }

    // Sort strip by Y coordinate
    sort(strip.begin(), strip.end(), compareY);

    // Check only nearby points in the strip
    // It's mathematically proven we only need to check the next 7 points
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    return d;
}

double minimal_distance(vector<int> x, vector<int> y) {
    int n = x.size();
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) {
        pts[i] = {x[i], y[i]};
    }

    // Pre-sort by X coordinate to enable the divide and conquer split
    sort(pts.begin(), pts.end(), compareX);

    return find_minimal_distance(pts, 0, n);
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    size_t n;
    if (cin >> n) {
        vector<int> x(n), y(n);
        for (size_t i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }
        
        // Output result with the required precision
        cout << fixed << setprecision(9) << minimal_distance(x, y) << "\n";
    }
    
    return 0;
}
