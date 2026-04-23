# 🧠 Course 5: Advanced Algorithms and Complexity

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2F17-00599C?style=for-the-badge&logo=c%2B%2B)
![Skill](https://img.shields.io/badge/Skill-NP--Completeness_%26_Optimization-success?style=for-the-badge)

Welcome to the fifth module of the UC San Diego Data Structures and Algorithms Specialization. 

This directory contains my optimized C++ solutions for **Advanced Algorithms and Complexity**. This course is widely considered the most mathematically rigorous in the specialization. It transitions from traditional polynomial-time algorithms into the realm of optimization and computational intractability, focusing heavily on Network Flows, Linear Programming, and coping with NP-Complete problems.

---

## 📚 Topics & Module Breakdown

### Week 1: Flows in Networks
* **Focus:** Modeling transportation, plumbing, and matching problems using flow networks. Implementing Ford-Fulkerson and Edmonds-Karp to find bottlenecks and maximum throughput.
* **Key Problems:**
  * Evacuating People (Maximum Flow using Edmonds-Karp)
  * Assigning Airline Crews to Flights (Bipartite Matching reduced to Max Flow)
  * Stock Charts (Minimum Path Cover in a Directed Acyclic Graph)

### Week 2: Linear Programming
* **Focus:** Solving massive optimization equations using the Simplex algorithm. Formulating real-world constraints into mathematical inequalities.
* **Key Problems:**
  * Inferring Energy Values of Ingredients (Gaussian Elimination for systems of linear equations)
  * The Diet Problem (Linear Programming to optimize nutrition costs within bounds)

### Week 3: NP-Complete Problems
* **Focus:** Understanding problems where no fast (polynomial-time) solution is known to exist. Learning the art of **Problem Reduction**: mapping new problems into known NP-Complete formats to utilize highly optimized SAT solvers.
* **Key Problems:**
  * Assigning Frequencies to Cell Towers (Reducing Graph 3-Coloring to Boolean Satisfiability / SAT in DIMACS CNF format)
  * Cleaning the Apartment (Reducing the Hamiltonian Path problem to SAT)
  * Advertisement Revenue (Maximum Independent Set)

### Week 4: Coping with NP-Completeness
* **Focus:** When you *must* solve an NP-Complete problem, how do you do it? Using exact exponential algorithms, branch-and-bound, and dynamic programming to speed up brute-force methods from $O(N!)$ down to $O(N^2 2^N)$.
* **Key Problems:**
  * Integrated Circuit Design (2-SAT problem solved via Strongly Connected Components in $O(V+E)$ time)
  * Plan a Fun Party (Maximum Independent Set on Trees using Dynamic Programming)
  * Traveling Salesman Problem (TSP) (Optimized via Bitmask Dynamic Programming)

---

## ⚡ Technical Highlights

* **Algorithm Reductions:** A major highlight of this module is writing C++ code that doesn't solve a problem directly, but instead acts as a compiler—generating a massive Boolean formula to be processed by a downstream SAT solver.
* **Bitmask Dynamic Programming:** Implemented highly memory-efficient TSP solutions using bitwise operators (`1 << i`) to track visited cities, turning a computationally impossible $O(N!)$ factorial problem into a solvable $O(N^2 2^N)$ state-space.
* **Graph Residuals:** Managed complex residual networks for the Edmonds-Karp algorithm, ensuring forward and backward edges updated synchronously to prevent infinite loops in flow graphs.

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
* [Return to Course 4: Algorithms on Strings](../Course_4_Algorithms_on_Strings)
* [Return to Main Specialization Repository](../README.md)
* [Proceed to Course 6: Genome Assembly Programming Challenge](../Course_6_Genome_Assembly_Programming_Challenge)
