# 🔤 Course 4: Algorithms on Strings

![C++](https://img.shields.io/badge/Language-C%2B%2B14%2F17-00599C?style=for-the-badge&logo=c%2B%2B)
![Skill](https://img.shields.io/badge/Skill-Text_Processing_%26_Bioinformatics-success?style=for-the-badge)

Welcome to the fourth module of the UC San Diego Data Structures and Algorithms Specialization. 

This directory contains my optimized C++ solutions for **Algorithms on Strings**. This course shifts focus from standard graphs to text processing, string matching, and the foundational algorithms used in modern search engines and bioinformatics (like mapping DNA reads to a reference genome). 

---

## 📚 Topics & Module Breakdown

### Week 1: Suffix Trees
* **Focus:** Transitioning from single pattern matching to multiple pattern matching. Implementing Tries and compressing them into Suffix Trees to search massive texts efficiently.
* **Key Problems:**
  * Construct a Trie from a Collection of Patterns
  * Multiple Pattern Matching
  * Construct the Suffix Tree of a String (Handling $O(N^2)$ naive construction limits)

### Week 2: Burrows-Wheeler Transform and Suffix Arrays
* **Focus:** Data compression and memory-efficient string representations. The BWT is the engine behind modern genome aligners (like BWA and Bowtie) and file compression protocols (like bzip2).
* **Key Problems:**
  * Construct the Burrows-Wheeler Transform (BWT) of a String
  * Reconstruct a String from its BWT
  * Pattern Matching with the BWT (Using First-Last property and count arrays)
  * Construct the Suffix Array of a String

### Week 3: Knuth-Morris-Pratt (KMP) Algorithm
* **Focus:** Exact pattern matching in $O(|Text| + |Pattern|)$ time. Avoiding redundant character comparisons by precomputing a prefix function.
* **Key Problems:**
  * Find All Occurrences of a Pattern in a String (Using KMP)
  * Construct the Prefix Function of a String

### Week 4: Constructing Suffix Arrays and Suffix Trees
* **Focus:** Scaling up. A naive Suffix Array takes $O(N^2 \log N)$, which fails on large datasets. This week focuses on implementing the $O(N \log N)$ Suffix Array construction algorithm and generating Suffix Trees from Suffix Arrays + LCP (Longest Common Prefix) arrays.
* **Key Problems:**
  * Construct a Suffix Array in $O(N \log N)$ Time (Using character equivalence classes)
  * Pattern Matching with the Suffix Array
  * Construct the Suffix Tree from the Suffix Array

---

## ⚡ Technical Highlights

* **Memory-Efficient Data Structures:** A standard Suffix Tree can easily consume massive amounts of memory. These solutions heavily utilize Suffix Arrays (which only require an array of integers) combined with LCP arrays to achieve Suffix Tree performance without the massive overhead.
* **Advanced String Compression:** Implemented the full Burrows-Wheeler Transform pipeline from scratch, optimizing the First-Last mapping arrays to execute complex pattern matching in sub-linear time.
* **Robust Pointer & Index Management:** Safely translating tree structures into 1D arrays to avoid `SIGSEGV` errors and maintain CPU cache efficiency during high-speed text processing.

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
* [Return to Course 3: Algorithms on Graphs](../Course_3_Algorithms_on_Graphs)
* [Return to Main Specialization Repository](../README.md)
* [Proceed to Course 5: Advanced Algorithms and Complexity](../Course_5_Advanced_Algorithms_and_Complexity)
