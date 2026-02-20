#  Tree Data Structures Performance Benchmark

A high-performance C application designed to evaluate and compare the efficiency of three fundamental search tree algorithms: **Simple BST**, **AVL**, and **Red-Black Tree**.

###  Project Structure
* **src/**: Core implementation (.c) of tree algorithms and benchmarking logic.
* **include/**: Header files (.h) with structure definitions and prototypes.
* **database_generator/**: Utility for generating randomized input datasets.

### 📊 Performance Summary (Stress Test)
Results recorded after **10,000 search operations** and **100 deletions**:

| Data Structure | Insertion (ms) | Search (ms) | Deletion (ms) |
| :--- | :---: | :---: | :---: |
| **Simple BST** | 1.00 | 2.80 | < 0.1 |
| **AVL Tree** | 0.60 | 1.80 | 0.20 |
| **Red-Black Tree** | 0.60 | 2.20 | 0.60 |

> **Key Insight:** AVL trees showed the best search performance due to strict balancing, while Red-Black trees provided a highly efficient balance between insertions and lookups.


### How to Run (Build & Execute)
Copy and paste the command below into your terminal to compile and run everything in one step:

Bash
gcc -I include database_generator/generate_dataset.c -o generator.exe && ./generator.exe &

Technical Implementation
Language: C
Concepts: Self-balancing algorithms, $O(\log n)$ Time Complexity, Manual Memory Management.
Benchmark: Real-time performance tracking for core tree operations.
