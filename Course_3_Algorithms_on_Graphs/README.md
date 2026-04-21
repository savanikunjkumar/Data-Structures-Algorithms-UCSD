# Course 3: Algorithms on Graphs 🕸️

This directory contains my C++ solutions for **Algorithms on Graphs**, the third course in the UC San Diego Data Structures and Algorithms Specialization. 

The focus of this course is on modeling real-world problems as networks (graphs) and implementing efficient algorithms to traverse them, find shortest paths, and build minimum spanning trees.

## 🧠 Core Concepts Covered

* **Decomposition of Graphs:** * Traversing graphs using Depth-First Search (DFS).
  * Finding connected components and determining reachability.
  * Topological sorting and finding Strongly Connected Components (SCCs) in directed graphs.
* **Paths in Graphs:** * Finding the shortest path in unweighted graphs using Breadth-First Search (BFS).
  * Computing shortest paths in weighted graphs using Dijkstra's Algorithm.
  * Handling graphs with negative edge weights using the Bellman-Ford algorithm and detecting negative cycles.
* **Minimum Spanning Trees (MST):** * Connecting a network with the minimum possible total edge weight using Kruskal's and Prim's algorithms.
  * Utilizing Disjoint Sets (Union-Find) and Priority Queues for optimal MST construction.

## 💻 Technical Approach

All implementations are written in **C++**.
* **Graph Representation:** Focus on using Adjacency Lists (`std::vector<std::vector<int>>` or `std::vector<std::vector<pair<int, int>>>`) rather than Adjacency Matrices to optimize space complexity for sparse graphs.
* **STL Integration:** Heavy reliance on standard C++ containers such as `std::queue` for BFS and `std::priority_queue` for optimal implementations of Dijkstra's and Prim's algorithms.

---

### ⚠️ Academic Integrity & Anti-Plagiarism Notice

**Please Read Before Reviewing This Code:**

This repository serves as a personal portfolio to showcase my problem-solving skills and algorithmic growth. 

* **Strictly Do Not Copy:** If you are currently enrolled in this course, copying these solutions and submitting them as your own is a direct violation of the UC San Diego and Coursera Honor Code. 
* **Consequences:** Automated plagiarism detection systems will flag identical submissions, which can result in the revocation of your certificate and a ban from the platform.
* **Learn, Don't Cheat:** You are welcome to review my code to understand the logic and approach after you have attempted the problems yourself, but you must write your own implementations.

*Authored and maintained by Kunjkumar Savani.*
