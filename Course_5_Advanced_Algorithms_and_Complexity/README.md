# Course 5: Advanced Algorithms and Complexity 🧠

This directory contains my C++ solutions for **Advanced Algorithms and Complexity**, the fifth course in the UC San Diego Data Structures and Algorithms Specialization. 

The focus of this course is on solving massive, highly constrained real-world optimization problems. It covers network flows, linear programming, and strategies for dealing with computationally intractable (NP-complete) problems.

## 🧠 Core Concepts Covered

* **Flows in Networks:** Modeling systems as flow networks to solve routing and allocation problems. Implementing the Ford-Fulkerson algorithm and Edmonds-Karp algorithm to find the Maximum Flow and Minimum Cut.
* **Linear Programming:** Formulating complex optimization problems as Integer Linear Programming (ILP) models to maximize or minimize an objective function subject to constraints.
* **NP-Complete Problems:** Understanding the P vs. NP problem. Learning how to mathematically reduce classic NP-complete problems (like Graph Coloring, Hamiltonian Path, and Vertex Cover) into Boolean Satisfiability (SAT) formulas.
* **Coping with NP-Completeness:** Since NP-complete problems cannot be solved efficiently in the worst case, this module focuses on practical workarounds using Exact Exponential Algorithms, Approximation Algorithms, Branch and Bound, and Heuristics.

## 💻 Technical Approach

All implementations are written in **C++**.
* **SAT Solvers:** Heavy emphasis on generating logical constraints in Conjunctive Normal Form (CNF) to be passed into automated SAT solvers (like standard MiniSat).
* **Algorithmic Reductions:** Code focuses heavily on translating graphs and linear inequalities into Boolean variables and clauses efficiently, strictly adhering to maximum clause/variable limits.

---

### ⚠️ Academic Integrity & Anti-Plagiarism Notice

**Please Read Before Reviewing This Code:**

This repository serves as a personal portfolio to showcase my problem-solving skills and algorithmic growth. 

* **Strictly Do Not Copy:** If you are currently enrolled in this course, copying these solutions and submitting them as your own is a direct violation of the UC San Diego and Coursera Honor Code. 
* **Consequences:** Automated plagiarism detection systems will flag identical submissions, which can result in the revocation of your certificate and a ban from the platform.
* **Learn, Don't Cheat:** You are welcome to review my code to understand the logic and approach after you have attempted the problems yourself, but you must write your own implementations.

*Authored and maintained by Kunjkumar Savani.*
