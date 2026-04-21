# Course 6: Genome Assembly Programming Challenge 🧬🔬

This directory contains my C++ solutions for the **Genome Assembly Programming Challenge**, the final capstone course in the UC San Diego Data Structures and Algorithms Specialization. 

Unlike previous courses that focused on isolated algorithmic puzzles, this course is a comprehensive project. It focuses on the computational biology techniques used to piece together the genome of a deadly bacterial pathogen (based on the real-world 2011 European *E. coli* outbreak) using millions of short DNA reads.

## 🧠 Core Concepts Covered

* **The 2011 European E. coli Outbreak:** Understanding the biological context of DNA sequencing and the computational challenge of the "Fragment Assembly" problem.
* **De Bruijn Graphs:** Breaking sequence reads into smaller overlapping segments (*k-mers*) to construct massive, directed De Bruijn graphs.
* **Eulerian Paths:** Reconstructing the full genome by finding a path that visits every edge in the De Bruijn graph exactly once.
* **Handling Real Sequencing Data:** Real-world DNA reads (like those from Illumina sequencers) contain errors. This module focuses on error correction techniques, such as bubble popping and tip removal in graphs, to accurately assemble contigs.

## 💻 Technical Approach

All implementations are written in **C++**.
* **Massive Data Processing:** The final challenges involve processing millions of DNA strings. The code heavily emphasizes optimized memory management and execution speed to stay within strict limits.
* **Advanced Graph Traversal:** Applying modified graph algorithms (Eulerian Cycles/Paths) to structures with millions of nodes and edges, requiring highly efficient Adjacency List representations.

---

### ⚠️ Academic Integrity & Anti-Plagiarism Notice

**Please Read Before Reviewing This Code:**

This repository serves as a personal portfolio to showcase my problem-solving skills and algorithmic growth. 

* **Strictly Do Not Copy:** If you are currently enrolled in this course, copying these solutions and submitting them as your own is a direct violation of the UC San Diego and Coursera Honor Code. 
* **Consequences:** Automated plagiarism detection systems will flag identical submissions, which can result in the revocation of your certificate and a ban from the platform.
* **Learn, Don't Cheat:** You are welcome to review my code to understand the logic and approach after you have attempted the problems yourself, but you must write your own implementations.

*Authored and maintained by Kunjkumar Savani.*
