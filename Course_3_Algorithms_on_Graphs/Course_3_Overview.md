# 🕸️ Course 3: Algorithms on Graphs

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2F17-00599C?style=for-the-badge&logo=c%2B%2B)
![Skill](https://img.shields.io/badge/Skill-Graph_Theory_%26_Routing-success?style=for-the-badge)

Welcome to the third module of the UC San Diego Data Structures and Algorithms Specialization. 

This directory contains my optimized C++ solutions for **Algorithms on Graphs**. This course transitions from linear and hierarchical data structures into complex network routing, focusing on how to model real-world infrastructures (road networks, internet topologies, social networks) mathematically and traverse them efficiently.

---

## 📚 Topics & Module Breakdown

### Week 1: Graph Decomposition 1 (Undirected Graphs)
* **Focus:** Basic graph representations (Adjacency Lists vs. Matrices) and exploring undirected networks to find paths and isolated components.
* **Key Problems:**
  * Finding an Exit from a Maze (Depth-First Search / DFS)
  * Adding Exits to a Maze (Counting Connected Components)

### Week 2: Graph Decomposition 2 (Directed Graphs)
* **Focus:** Navigating one-way networks, detecting dependencies, and grouping mutually reachable nodes.
* **Key Problems:**
  * Checking Consistency of CS Curriculum (Cycle Detection in Directed Graphs)
  * Determining an Order of Courses (Topological Sort)
  * Checking if Any Intersection in a City is Reachable from Any Other (Strongly Connected Components using Kosaraju's or Tarjan's Algorithm)

### Week 3: Paths in Graphs 1 (Unweighted Graphs)
* **Focus:** Finding the *shortest* path in terms of the sheer number of edges, and exploring network colorability.
* **Key Problems:**
  * Computing the Minimum Number of Flight Segments (Breadth-First Search / BFS)
  * Checking whether a Graph is Bipartite (2-Coloring via BFS)

### Week 4: Paths in Graphs 2 (Weighted Graphs)
* **Focus:** Real-world shortest paths where edges have varying costs (time, distance, money). Handling the dreaded "negative weight" scenarios.
* **Key Problems:**
  * Computing the Minimum Cost of a Flight (Dijkstra's Algorithm using Min-Heaps)
  * Detecting Anomalies in Currency Exchange Rates (Negative Cycle Detection via Bellman-Ford Algorithm)
  * Exchanging Money Optimally (Finding all nodes reachable from negative cycles)

### Week 5: Minimum Spanning Trees
* **Focus:** Connecting a network of nodes with the absolute minimum total edge weight. 
* **Key Problems:**
  * Building Roads to Connect Cities (Prim's or Kruskal's Algorithm)
  * Clustering (Applying Kruskal's algorithm with a custom stopping condition to maximize distance between $k$ clusters, foundational for machine learning)

### Week 6: Advanced Shortest Paths (Optional/Advanced)
* **Focus:** Scaling shortest path algorithms to massive real-world road networks (millions of nodes) where standard Dijkstra is too slow.
* **Key Concepts:** Bidirectional Dijkstra and A* (A-Star) Search heuristics.

---

## ⚡ Technical Highlights

* **Adjacency List Optimization:** Storing graphs using `std::vector<std::vector<int>>` rather than adjacency matrices to ensure $O(V + E)$ time complexity and prevent $O(V^2)$ memory limits on sparse graphs with $10^5$ vertices.
* **Priority Queue Integration:** Standard Dijkstra runs in $O(V^2)$. These solutions implement Dijkstra using C++ `std::priority_queue` to achieve $O((V + E) \log V)$ performance, which is mandatory to pass the auto-grader's strict 1.0s execution limits.
* **Disjoint Sets for MST:** Leveraged the highly optimized Union-Find data structure (with path compression and union by rank) built in Course 2 to execute Kruskal’s Algorithm efficiently.

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
* [Return to Course 2: Data Structures](../Course_2_Data_Structures)
* [Return to Main Specialization Repository](../README.md)
* [Proceed to Course 4: Algorithms on Strings](../Course_4_Algorithms_on_Strings)
