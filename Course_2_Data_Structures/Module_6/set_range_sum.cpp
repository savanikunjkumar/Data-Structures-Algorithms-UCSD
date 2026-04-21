/*
 * Author: Kunjkumar Savani
 * Course: Data Structures and Algorithms by UC San Diego
 * Module: Course 2, Module 6
 * Assignment: Is it a binary search tree?
 *
 * The Problem: Determine if a given binary tree is a valid Binary Search Tree (BST).
 * * The Logic: The most elegant and efficient way to verify a BST is to perform an 
 * In-order traversal. In a mathematically valid BST, an in-order traversal guarantees 
 * that the nodes will be visited in strictly ascending numerical order. To avoid 
 * Stack Overflow (Runtime Error) on deeply skewed trees, we use an iterative stack 
 * approach instead of naive recursion. We simply keep track of the previously visited 
 * node's value (`prev`) and ensure every current node is strictly greater than it. 
 * This perfectly handles the validation in O(N) time and O(N) space.
 */

#include <iostream>
#include <cstdio>

using namespace std;

struct Vertex {
    int key;
    long long sum;
    Vertex* left;
    Vertex* right;
    Vertex* parent;
    Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent) 
    : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
    if (v == NULL) return;
    v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
    if (v->left != NULL) v->left->parent = v;
    if (v->right != NULL) v->right->parent = v;
}

void small_rotation(Vertex* v) {
    Vertex* parent = v->parent;
    if (parent == NULL) return;
    Vertex* grandparent = v->parent->parent;
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
    if (grandparent != NULL) {
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
    if (v == NULL) return;
    while (v->parent != NULL) {
        if (v->parent->parent == NULL) {
            small_rotation(v);
            break;
        }
        big_rotation(v);
    }
    root = v;
}

Vertex* find(Vertex*& root, int key) {
    Vertex* v = root;
    Vertex* last = root;
    Vertex* next = NULL;
    while (v != NULL) {
        if (v->key >= key && (next == NULL || v->key < next->key)) next = v;
        last = v;
        if (v->key == key) break;      
        if (v->key < key) v = v->right;
        else v = v->left;
    }
    splay(root, last);
    return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
    right = find(root, key);
    splay(root, right);
    if (right == NULL) {
        left = root;
        return;
    }
    left = right->left;
    right->left = NULL;
    if (left != NULL) left->parent = NULL;
    update(left);
    update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;
    Vertex* min_right = right;
    while (min_right->left != NULL) min_right = min_right->left;
    splay(right, min_right);
    right->left = left;
    update(right);
    return right;
}

Vertex* root = NULL;

void insert(int x) {
    Vertex* left = NULL;
    Vertex* right = NULL;
    Vertex* new_vertex = NULL;  
    split(root, x, left, right);
    if (right == NULL || right->key != x) {
        new_vertex = new Vertex(x, x, NULL, NULL, NULL);
    }
    root = merge(merge(left, new_vertex), right);
}

bool find_key(int x) {  
    Vertex* result = find(root, x);
    return (result != NULL && result->key == x);
}

void erase(int x) {                   
    if (find_key(x)) {
        Vertex* old_root = root;
        Vertex* left = root->left;
        Vertex* right = root->right;
        if (left != NULL) left->parent = NULL;
        if (right != NULL) right->parent = NULL;
        root = merge(left, right);
        delete old_root;
    }
}

long long sum(int from, int to) {
    Vertex* left = NULL;
    Vertex* middle = NULL;
    Vertex* right = NULL;
    split(root, from, left, middle);
    split(middle, to + 1, middle, right);
    long long ans = 0;
    if (middle != NULL) ans = middle->sum;
    middle = merge(middle, right);
    root = merge(left, middle);
    return ans;  
}

const int MODULO = 1000000001;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
        string type;
        cin >> type;
        if (type == "+") {
            int x;
            cin >> x;
            insert((x + last_sum_result) % MODULO);
        } else if (type == "-") {
            int x;
            cin >> x;
            erase((x + last_sum_result) % MODULO);
        } else if (type == "?") {
            int x;
            cin >> x;
            cout << (find_key((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
        } else if (type == "s") {
            int l, r;
            cin >> l >> r;
            long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
            cout << res << "\n";
            last_sum_result = int(res % MODULO);
        }
    }
    return 0;
}
