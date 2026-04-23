# University Of California  San Diego: Data Structures and Algorithms Specialization

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2F17-00599C?style=for-the-badge&logo=c%2B%2B)
![Algorithms](https://img.shields.io/badge/Focus-Data_Structures_%26_Algorithms-blueviolet?style=for-the-badge)
![Institution](https://img.shields.io/badge/Institution-UC_San_Diego_%26_HSE-FFCD00?style=for-the-badge)

Welcome to my comprehensive repository for the **Data Structures and Algorithms Specialization**, jointly offered by **UC San Diego (UCSD)** and **HSE University-Russia** via Coursera. 

This repository houses my highly optimized, competitive-programming-grade **C++ solutions** for all 6 courses within the specialization. Every algorithm implemented here was designed to pass rigorous automated testing, strictly adhering to tight memory limits (often < 512MB) and execution time limits (typically < 1.0s on 10⁵ constraints).

---

## 👨‍💻 Author & Credentials

* **Author:** Kunjkumar Savani
* **Email:** savani.kunjkumr@gmail.com
* **LinkedIn:** https://www.linkedin.com/in/kunj-savani-08a38937a/
* **ORCID:** https://orcid.org/0009-0005-1863-6757
* **Official Specialization Certificate:** https://coursera.org/verify/specialization/7P3FXODKCGFQ

---

## 🛠️ Technical Highlights & Optimizations

To conquer the advanced modules of this specialization, standard coding practices were often not enough. Key optimizations implemented across this repository include:
* **Fast I/O:** Bypassing standard stream synchronization (`ios_base::sync_with_stdio(false); cin.tie(NULL);`) to handle massive inputs.
* **Iterative Tree Traversals:** Converting standard recursive Depth-First Searches (DFS) into iterative stack-based approaches to prevent `SIGSEGV` (Stack Overflow) errors on graphs with extreme depth.
* **Bitmasking & State Compression:** Used heavily in Dynamic Programming (e.g., the Traveling Salesman Problem) to reduce exponential memory overhead.
* **Problem Reductions:** Mapping real-world constraints into Integer Linear Programming (ILP) and Boolean Satisfiability (SAT) formulas to handle NP-Complete problems.

---

## 🛤️ Course Directory & Navigation

Explore the solutions by navigating to the respective course directories below.

### [📁 Course 1: Algorithmic Toolbox](./Course_1_Algorithmic_Toolbox)

* **Focus:** Essential algorithmic techniques.
* **Topics:** Greedy Algorithms, Divide and Conquer, introductory Dynamic Programming, and foundational mathematical algorithms (GCD, Fibonacci optimizations).

### [📁 Course 2: Data Structures](./Course_2_Data_Structures)

* **Focus:** The structural backbone of efficient software.
* **Topics:** Dynamic Arrays, Disjoint Sets (Union-Find), Hash Tables, Priority Queues, and Binary Search Trees.

### [📁 Course 3: Algorithms on Graphs](./Course_3_Algorithms_on_Graphs)

* **Focus:** Modeling networks and pathfinding.
* **Topics:** Graph traversals (BFS/DFS), Strongly Connected Components, Shortest Paths (Dijkstra, Bellman-Ford), and Minimum Spanning Trees (Kruskal, Prim).

### [📁 Course 4: Algorithms on Strings](./Course_4_Algorithms_on_Strings)

* **Focus:** Text processing and pattern matching.
* **Topics:** Tries, Suffix Trees, Suffix Arrays, Knuth-Morris-Pratt (KMP), and the Burrows-Wheeler Transform (BWT).

### [📁 Course 5: Advanced Algorithms and Complexity](./Course_5_Advanced_Algorithms_and_Complexity)

* **Focus:** Tackling mathematically hard problems.
* **Topics:** Max Flow (Edmonds-Karp), Bipartite Matching, Linear Programming, and coping with NP-Completeness through exact algorithms and SAT reductions.

### [📁 Course 6: Genome Assembly Programming Challenge](.Course_6_Genome_Assembly_Programming_Challenge)

* **Focus:** The Capstone Project. Applied Bioinformatics.
* **Topics:** Assembling the φ X174 genome from error-prone reads using De Bruijn Graphs, finding Eulerian Cycles (Hierholzer’s Algorithm), Tip Removal, and Bounded DFS Bubble Detection.

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
