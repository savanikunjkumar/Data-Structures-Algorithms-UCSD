# 🧬 Course 6: Genome Assembly Programming Challenge

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2F17-00599C?style=for-the-badge&logo=c%2B%2B)
![Skill](https://img.shields.io/badge/Skill-Bioinformatics_%26_Graph_Theory-success?style=for-the-badge)

Welcome to the final module of the UC San Diego Data Structures and Algorithms Specialization!

This directory contains my optimized C++ solutions for the **Genome Assembly Programming Challenge**. This capstone project ties together everything learned in the previous five courses. It transitions from theoretical computer science into applied Bioinformatics, challenging us to build an end-to-end genome assembler that reconstructs the circular $\phi$ X174 genome from millions of short, error-prone DNA reads.

---

## 📚 Topics & Module Breakdown

### Module 1: Assembling the $\phi$ X174 Genome using Overlap Graphs
* **Focus:** The naive approach to assembly. Modeling reads as nodes and overlaps as edges to find a Hamiltonian Path (the Shortest Superstring Problem).
* **Key Problems:**
  * Assembling the Genome Using a Greedy Approach (Approximating the NP-Hard Shortest Superstring problem).
  * Error-Free Assembly using exact overlap matching.

### Module 2: Assembling Genomes using De Bruijn Graphs
* **Focus:** Moving from NP-Hard Hamiltonian Paths to $O(V+E)$ Eulerian Cycles. Breaking reads into $k$-mers to build highly efficient De Bruijn graphs.
* **Key Problems:**
  * Puzzle Assembly (Backtracking with boundary pruning).
  * Finding an Eulerian Cycle in a Directed Graph (Hierholzer’s Algorithm).
  * Finding a $k$-Universal Circular String (De Bruijn Sequences).
  * Assembling the $\phi$ X174 Genome from its $k$-mer Composition (Perfect, error-free assembly).

### Module 3: Genome Assembly Faces Real Sequencing Data
* **Focus:** Real-world Illumina sequencing machines make mistakes (typically a 1% error rate). This module focuses on error correction algorithms to clean the De Bruijn graph before assembly.
* **Key Problems:**
  * Finding a Circulation in a Network (Reducing bounded flow demands to a Standard Max Flow problem).
  * Selecting the Optimal $k$-mer Size (Balancing graph connectivity and repeat resolution).
  * **Tip Removal:** Pruning dead-end branches caused by errors at the ends of reads.
  * **Bubble Detection:** Using Bounded Depth-First Search (DFS) to find and pop disjoint paths caused by single-nucleotide mutations.

### Final Project: Implementing a Complete Assembler
* **Focus:** The ultimate test. Combining read pairing, dynamic $k$-mer generation, Tip Removal, Bubble Detection, and Eulerian path extraction to assemble contigs from a massive, error-prone dataset. Evaluated against industry-standard assemblers (like SPAdes) using the NGA50 metric.

---

## ⚡ Technical Highlights

* **Memory-Optimized Graphs:** Storing millions of 100-character DNA strings in RAM causes instant Out-Of-Memory (OOM) errors. These solutions dynamically map unique string $(k-1)$-mers to integer IDs, allowing the graph to be represented as a highly efficient integer Adjacency List.
* **Advanced Graph Cleaning:** Implemented queue-based zero-degree pruning for Tip Removal and a highly tuned Bounded DFS to detect reconverging bubbles within strict time limits.
* **Network Flow Reduction:** Successfully modeled the complex Scaffold Circulation problem as a standard Maximum Flow problem, utilizing the Edmonds-Karp algorithm built in Course 5 with Super-Source and Super-Sink balancing.

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
* [Return to Course 5: Advanced Algorithms and Complexity](../Course_5_Advanced_Algorithms_and_Complexity)
* [Return to Main Specialization Repository](../README.md)
