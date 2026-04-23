# 🗄️ Course 2: Data Structures

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2F17-00599C?style=for-the-badge&logo=c%2B%2B)
![Skill](https://img.shields.io/badge/Skill-Memory_%26_State_Management-success?style=for-the-badge)

Welcome to the second module of the UC San Diego Data Structures and Algorithms Specialization. 

This directory contains my optimized C++ solutions for the **Data Structures** course. While Course 1 focused on algorithmic logic, this course dives deep into the underlying mechanics of how data is stored, retrieved, and manipulated in memory. Mastery here is the difference between an algorithm that times out (Time Limit Exceeded) and one that executes instantly.

---

## 📚 Topics & Module Breakdown

### Week 1: Basic Data Structures
* **Focus:** Fundamental memory organization. Arrays, Linked Lists, Stacks, Queues, and basic Tree representations. Handling deep recursion limits in C++.
* **Key Problems:**
  * Check brackets in the code (Stack application)
  * Compute tree height (Handling massive $10^5$ unbalanced trees)
  * Network packet processing simulation (Queue/Buffer mechanics)

### Week 2: Priority Queues and Disjoint Sets
* **Focus:** Fast element retrieval and dynamic connectivity. Implementing Heaps from scratch and mastering the Union-Find data structure with path compression and union by rank.
* **Key Problems:**
  * Convert array into heap (Build Heap in $O(N)$)
  * Parallel processing (Simulating a job queue using Min-Heaps)
  * Merging tables (Disjoint Sets / Union-Find)

### Week 3: Hash Tables
* **Focus:** $O(1)$ average-case search times. Understanding hash functions, universal hashing families, and resolving collisions via chaining.
* **Key Problems:**
  * Phone book simulation (Direct addressing)
  * Hashing with chains 
  * Find pattern in text (Rabin-Karp algorithm using polynomial rolling hashes)

### Week 4 & 5: Binary Search Trees
* **Focus:** Dynamic sets supporting logarithmic search, insert, and delete. Progressing from naive BSTs to self-balancing trees (AVL / Splay Trees).
* **Key Problems:**
  * Binary tree traversals (In-order, Pre-order, Post-order)
  * Is it a BST? (Validating tree properties, including hard cases with duplicate values)
  * Set with range sums (Implementing a Splay Tree from scratch to handle dynamic range queries)
  * Rope String Data Structure (Advanced Splay tree application for $O(\log N)$ string manipulations)

---

## ⚡ Technical Highlights

* **Recursion Depth Safety:** Several tree problems in this module feature highly unbalanced test cases (e.g., $10^5$ nodes in a single line). Naive recursive DFS solutions will result in `SIGSEGV` (Stack Overflow). These solutions utilize custom iterative stack traversals or `#pragma` directives to safely navigate extreme depths.
* **Custom Implementations:** While the C++ STL provides `std::priority_queue` and `std::unordered_set`, several assignments required building Disjoint Sets, Min-Heaps, and Splay Trees entirely from scratch to handle custom properties (like tracking sub-tree sums).

---

## ⚠️ Academic Integrity & Anti-Plagiarism Notice

> **Please Read Before Reviewing This Code:**
> 
> This repository serves as a personal portfolio to showcase my problem-solving skills and technical growth. 
> 
> * **Strictly Do Not Copy:** If you are currently enrolled in this course, copying these solutions and submitting them as your own is a direct violation of the UC San Diego and Coursera Honor Code. 
> * **Consequences:** Automated plagiarism detection systems will flag identical submissions, which can result in the revocation of your certificate and a ban from the platform.
> * **Learn, Don't Cheat:** You are welcome to review my code to understand the logic and approach after you have attempted the problems yourself, but you must write your own implementations.
>
> *Authored and maintained by Kunjkumar Savani.*

---

### 🔙 Navigation
* [Return to Course 1: Algorithmic Toolbox](../Course_1_Algorithmic_Toolbox)
* [Return to Main Specialization Repository](../README.md)
* [Proceed to Course 3: Algorithms on Graphs](../Course_3_Algorithms_on_Graphs)
