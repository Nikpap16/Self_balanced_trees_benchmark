# Tree Data Structures Performance Benchmark

Μια εφαρμογή σε γλώσσα **C** για τη σύγκριση της αποδοτικότητας μεταξύ τριών τύπων δέντρων αναζήτησης: **Simple BST**, **AVL** και **Red-Black Tree**.

## 📁 Δομή Project
* `src/`: Ο πηγαίος κώδικας (.c) των δέντρων και του benchmark.
* `include/`: Τα αρχεία κεφαλίδας (.h) με τους ορισμούς των δομών.
* `database_generator/`: Εργαλείο δημιουργίας τυχαίων δεδομένων εισόδου.

## 📊 Σύνοψη Αποτελεσμάτων (Stress Test)
Μετά από 10.000 αναζητήσεις και 100 διαγραφές, καταγράφηκαν οι παρακάτω ενδεικτικοί χρόνοι:

| Δομή Δεδομένων | Insertion (sec) | Search (sec) | Deletion (sec) |
| :--- | :--- | :--- | :--- |
| **BST** | 0.001000 | 0.002800 | 0.000000 |
| **AVL** | 0.000600 | 0.001800 | 0.000200 |
| **Red-Black** | 0.000600 | 0.002200 | 0.000600 |



## 🚀 Οδηγίες Εκτέλεσης


##1. Προετοιμασία Δεδομένων
   
gcc -I include "database_generator/generate_dataset.c" -o generator.exe

Εκτέλεση
.\generator.exe


##2. Εκτέλεση Benchmark


gcc -I include src/*.c -o benchmark.exe

 Εκτέλεση
.\benchmark.exe
