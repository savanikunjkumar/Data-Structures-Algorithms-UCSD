/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Module 4
 * Assignment: Improving Quick Sort (3-Way Partition)
 */

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// 3-Way Partition (Dutch National Flag approach)
void partition3(vector<int> &a, int l, int r, int &m1, int &m2) {
    int pivot = a[l];
    int lt = l;  // Pointer for elements less than pivot
    int gt = r;  // Pointer for elements greater than pivot
    int i = l;   // Current iterator

    while (i <= gt) {
        if (a[i] < pivot) {
            swap(a[lt], a[i]);
            lt++;
            i++;
        } else if (a[i] > pivot) {
            swap(a[i], a[gt]);
            gt--;
        } else {
            i++;
        }
    }
    
    // Return boundaries of the "equal to pivot" section
    m1 = lt;
    m2 = gt;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }

    // Randomize the pivot to avoid worst-case scenarios on pre-sorted arrays
    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    
    int m1, m2;
    partition3(a, l, r, m1, m2);

    // Recursively sort ONLY the strictly less and strictly greater segments.
    // We completely ignore the a[m1 ... m2] segment because they are already sorted!
    randomized_quick_sort(a, l, m1 - 1);
    randomized_quick_sort(a, m2 + 1, r);
}

int main() {
    // Fast I/O for strict online grading time limits
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        randomized_quick_sort(a, 0, n - 1);
        
        for (int i = 0; i < n; ++i) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
