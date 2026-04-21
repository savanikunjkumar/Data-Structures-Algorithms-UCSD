# Course 4: Algorithms on Strings 🧬

This directory contains my C++ solutions for **Algorithms on Strings**, the fourth course in the UC San Diego Data Structures and Algorithms Specialization. 

The focus of this course is on string processing and pattern matching. Efficiently searching through massive texts is a fundamental problem in computer science, with direct applications in search engines, data compression, and bioinformatics (genomic sequencing).

## 🧠 Core Concepts Covered

* **Suffix Trees:** Constructing and navigating Suffix Tries and Suffix Trees for fast pattern matching and finding longest repeating substrings.
* **Burrows-Wheeler Transform (BWT) & Suffix Arrays:** Implementing BWT for data compression and using Suffix Arrays as a highly memory-efficient alternative to Suffix Trees.
* **Knuth-Morris-Pratt (KMP) Algorithm:** Achieving linear-time substring search by computing prefix functions and avoiding redundant character comparisons.
* **Advanced Construction:** Efficiently building Suffix Arrays and Suffix Trees in $O(n \log n)$ or $O(n)$ time to handle massive datasets.

## 💻 Technical Approach

All implementations are written in **C++**.
* **Memory Optimization:** String algorithms can easily exceed memory limits on large inputs (like entire genomes). A major focus here is replacing pointer-heavy Suffix Trees with array-based structures (like Suffix Arrays) to stay within the strict 512MB memory limits.
* **String Manipulation:** Heavy utilization of `std::string`, string views, and efficient substring indexing to avoid unnecessary copying overhead.

---

### ⚠️ Academic Integrity & Anti-Plagiarism Notice

**Please Read Before Reviewing This Code:**

This repository serves as a personal portfolio to showcase my problem-solving skills and algorithmic growth. 

* **Strictly Do Not Copy:** If you are currently enrolled in this course, copying these solutions and submitting them as your own is a direct violation of the UC San Diego and Coursera Honor Code. 
* **Consequences:** Automated plagiarism detection systems will flag identical submissions, which can result in the revocation of your certificate and a ban from the platform.
* **Learn, Don't Cheat:** You are welcome to review my code to understand the logic and approach after you have attempted the problems yourself, but you must write your own implementations.

*Authored and maintained by Kunjkumar Savani.*
