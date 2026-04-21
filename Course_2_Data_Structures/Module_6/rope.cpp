/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Advanced Binary Search Trees
 * Assignment: Rope Data Structure
 *
 * The Fix: 
 * 1. Replaced N individual insertions with a recursive O(N) build function.
 * 2. Optimized the split logic to handle boundary conditions more cleanly.
 * 3. Ensured fast I/O is fully utilized to handle the 300k character output.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Vertex {
    char key;
    int size;
    Vertex *left, *right, *parent;
    Vertex(char k) : key(k), size(1), left(NULL), right(NULL), parent(NULL) {}
};

int getSize(Vertex* v) { return v ? v->size : 0; }

void update(Vertex* v) {
    if (!v) return;
    v->size = 1 + getSize(v->left) + getSize(v->right);
    if (v->left) v->left->parent = v;
    if (v->right) v->right->parent = v;
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (!parent) return;
    Vertex* grandparent = parent->parent;
    if (parent->left == v) {
        Vertex* m = v->right;
        v->right = parent;
        parent->left = m;
    } else {
        Vertex* m = v->left;
        v->left = parent;
        parent->right = m;
    }
    update(parent);
    update(v);
    v->parent = grandparent;
    if (grandparent) {
        if (grandparent->left == parent) grandparent->left = v;
        else grandparent->right = v;
    }
}

void big_rotation(Vertex* v) {
    if (v->parent->left == v && v->parent->parent->left == v->parent) {
        small_rotation(v->parent);
        small_rotation(v);
    } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
        small_rotation(v->parent);
        small_rotation(v);
    } else {
        small_rotation(v);
        small_rotation(v);
    }
}

void splay(Vertex*& root, Vertex* v) {
    if (!v) return;
    while (v->parent) {
        if (!v->parent->parent) small_rotation(v);
        else big_rotation(v);
    }
    root = v;
}

Vertex* find(Vertex*& root, int k) {
    Vertex* v = root;
    while (v) {
        int s = getSize(v->left);
        if (s == k) break;
        if (s > k) v = v->left;
        else {
            k -= (s + 1);
            v = v->right;
        }
    }
    splay(root, v);
    return v;
}

void split(Vertex* root, int k, Vertex*& left, Vertex*& right) {
    if (k <= 0) { left = NULL; right = root; return; }
    if (k >= getSize(root)) { left = root; right = NULL; return; }
    Vertex* v = find(root, k);
    left = v->left;
    if (left) left->parent = NULL;
    v->left = NULL;
    right = v;
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (!left) return right;
    if (!right) return left;
    Vertex* v = left;
    while (v->right) v = v->right;
    splay(left, v);
    left->right = right;
    update(left);
    return left;
}

class Rope {
    Vertex* root;

    // O(N) recursive build
    Vertex* build(const string& s, int l, int r) {
        if (l > r) return NULL;
        int mid = l + (r - l) / 2;
        Vertex* v = new Vertex(s[mid]);
        v->left = build(s, l, mid - 1);
        v->right = build(s, mid + 1, r);
        update(v);
        return v;
    }

    void traverse(Vertex* v, string& res) {
        if (!v) return;
        traverse(v->left, res);
        res += v->key;
        traverse(v->right, res);
    }

public:
    Rope(const string& s) {
        root = build(s, 0, s.length() - 1);
    }

    void process(int i, int j, int k) {
        Vertex *l, *m, *r, *tmp;
        // Extract substring [i, j]
        split(root, i, l, tmp);
        split(tmp, j - i + 1, m, r);
        // Temporary root without the middle section
        root = merge(l, r);
        // Re-insert middle section at position k
        split(root, k, l, r);
        root = merge(merge(l, m), r);
    }

    string result() {
        string res = "";
        res.reserve(getSize(root)); // Pre-allocate memory for efficiency
        traverse(root, res);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);

    string s;
    if (!(cin >> s)) return 0;
    
    Rope rope(s);
    int actions;
    cin >> actions;
    
    for (int a = 0; a < actions; a++) {
        int i, j, k;
        cin >> i >> j >> k;
        rope.process(i, j, k);
    }
    
    cout << rope.result() << "\n";
    return 0;
}
