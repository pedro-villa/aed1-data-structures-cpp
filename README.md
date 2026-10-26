# Data Structures & Algebraic Specifications in C++17 & Maude

A collection of custom data structure implementations and formal algebraic specifications developed for *Algorithms and Data Structures I* (*Algoritmos y Estructuras de Datos I*).

The repository focuses on **low-level memory representation**, **pointer-based hierarchical structures**, **byte-level UTF-8 string normalization**, and **equational axiomatization of Abstract Data Types (ADTs)** without relying on high-level standard library tree/hash containers.

---

## Architectural Highlights

### 1. Memory-Compact LCRS Multiway Trie & Chained Hash Table ([`01-dictionary-trie-hashtable-cpp/`](./01-dictionary-trie-hashtable-cpp))
- **Left-Child Right-Sibling (LCRS) Pointer Layout**: Instead of allocating fixed 256-way pointer arrays per Trie node ($256 \times 8\text{ B} = 2\text{ KB}$ per node on 64-bit targets), each [`Nodo`](./01-dictionary-trie-hashtable-cpp/src/arbolTrie.h) stores only two pointers (`Nodo* hijo` and `Nodo* siguiente`) alongside sorted sibling lists, reducing memory overhead in sparse lexical trees by over $95\%$.
- **Subtree Height Augmentation for $O(|w| \cdot |\Sigma|)$ Prefix Completion**: Each Trie node maintains an incremental `altura` field tracking the maximum remaining suffix depth in its subtree. Longest-word prefix queries (`<alarga>`) greedily follow the highest-altitude child at each level without exhaustive subtree traversal or backtracking.
- **Byte-Level UTF-8 Spanish Normalization & 1-Byte Sentinel Compaction**:
  - [`modificar()`](./01-dictionary-trie-hashtable-cpp/src/004final.cpp) inspects raw UTF-8 `0xC3` lead bytes to fold accented Spanish vowels (`á, é, í, ó, ú` $\rightarrow$ `A, E, I, O, U`) while preserving `Ñ` (`0xC3 0x91`) and `Ü` (`0xC3 0x9C`).
  - [`convertir()`](./01-dictionary-trie-hashtable-cpp/src/arbolTrie.cpp) bijectively maps 2-byte UTF-8 sequences (`Ñ`, `Ü`) onto 1-byte ASCII sentinels (`'{'`, `'|'`), ensuring uniform 1-byte-per-level storage inside the Trie.
- **Ordered Separate-Chaining Hash Table**: [`TablaHash`](./01-dictionary-trie-hashtable-cpp/src/TablaHash.h) maintains sorted buckets for duplicate-free insertion, early-exit lookup, and lexicographical range extraction (`<saco>`).

### 2. Formal Algebraic ADT Specifications in Maude ([`02-algebraic-adts-maude/`](./02-algebraic-adts-maude))
- **26 Equational Specifications from First Principles**:
  - **Peano Arithmetic (`101`–`107`)**: Natural numbers constructed from `cero` and `sucesor`, integer division, binary logarithm, iterative $n$-th root approximation (`sucRaiz`), `mcd`, `mcm`, and coprimality.
  - **Linear ADTs (`110`–`118`)**: Equational axiomatization of Stacks (`Pila`), FIFO Queues (`Cola`), and Singly Linked Lists (`Lista`).
  - **Set & Multiset Algebra (`120`–`126`)**: Sets (`Conjunto`) with symmetric-difference equality and Multisets/Bags (`Bolsa`) with multiplicity tracking.
  - **Binary Search Trees & AVL Rotations (`140`–`144`)**: Recursive verification of BST ordering (`esOrdenado`), AVL height balance (`esAVL`), perfect node balance (`esPerfBal`), and explicit algebraic transformations for single (`rsd`, `rsi`) and double (`rdd`, `rdi`) AVL rotations.

---

## Complexity & Memory Summary

| Data Structure / Operation | Time Complexity (Worst Case) | Auxiliary Space | Implementation File |
| :--- | :--- | :--- | :--- |
| **LCRS Trie — Insert (`insertar`)** | $O(\|w\| \cdot \|\Sigma\|)$ | $O(\|w\|)$ new nodes | [`arbolTrie.cpp`](./01-dictionary-trie-hashtable-cpp/src/arbolTrie.cpp) |
| **LCRS Trie — Exact Lookup (`buscar`)** | $O(\|w\| \cdot \|\Sigma\|)$ | $O(1)$ | [`arbolTrie.cpp`](./01-dictionary-trie-hashtable-cpp/src/arbolTrie.cpp) |
| **LCRS Trie — Longest Prefix Match (`alarga`)** | $O(\|w_{\max}\| \cdot \|\Sigma\|)$ | $O(\|w_{\max}\|)$ | [`arbolTrie.cpp`](./01-dictionary-trie-hashtable-cpp/src/arbolTrie.cpp) |
| **Chained Hash Table — Insert / Lookup** | $O(n / B)$ avg, $O(n)$ worst | $O(n + B)$ | [`TablaHash.cpp`](./01-dictionary-trie-hashtable-cpp/src/TablaHash.cpp) |
| **Chained Hash Table — Range Query (`sacoPalabras`)** | $O(k + B)$ | $O(1)$ | [`TablaHash.cpp`](./01-dictionary-trie-hashtable-cpp/src/TablaHash.cpp) |
| **UTF-8 Normalization (`modificar` / `convertir`)** | $\Theta(\|w\|)$ | $O(\|w\|)$ | [`004final.cpp`](./01-dictionary-trie-hashtable-cpp/src/004final.cpp) |

*(where $|w|$ is word length, $|\Sigma| \le 29$ is the bounded alphabet branching factor per level, $B = 256$ is the bucket count, and $k$ is the number of words in the queried range).*

---

## Repository Structure

```text
aed1-data-structures-cpp/
├── README.md                                  # Architectural overview & build instructions
├── Makefile                                   # POSIX build & automated test runner
├── CMakeLists.txt                             # Modern CMake (ISO C++17) configuration
├── .gitignore
├── 01-dictionary-trie-hashtable-cpp/
│   ├── README.md                              # Deep dive: LCRS Trie, UTF-8 handling & Hash Table
│   ├── src/
│   │   ├── 004final.cpp                       # Command interpreter & UTF-8 byte normalizer
│   │   ├── diccionario.h / diccionario.cpp    # Dictionary facade (DicPalabras)
│   │   ├── arbolTrie.h / arbolTrie.cpp        # Height-augmented LCRS multiway Trie
│   │   └── TablaHash.h / TablaHash.cpp        # Ordered separate-chaining Hash Table
│   └── tests/
│       ├── sample_input.txt                   # Functional & UTF-8 edge-case test workload
│       ├── expected_output.txt                # Deterministic oracle output
│       └── run_tests.sh                       # Automated verification script
└── 02-algebraic-adts-maude/
    ├── README.md                              # Equational logic, BST invariants & AVL rotations
    └── specs/
        ├── 01-natural-numbers.maude           # Exercises 101-107: Peano arithmetic & number theory
        ├── 02-linear-structures.maude         # Exercises 110-118: Stacks, Queues, and Lists
        ├── 03-sets-and-bags.maude             # Exercises 120-126: Sets and Multisets (Bags)
        └── 04-binary-and-avl-trees.maude      # Exercises 140-144: Binary Trees, BSTs & AVL Rotations
```

---

## Build & Verification

### Using GNU Make

```bash
# Compile the C++17 dictionary engine with strict warnings (-Wall -Wextra -Wpedantic -O3)
make all

# Run the automated functional & UTF-8 test suite
make test

# Clean build artifacts
make clean
```

### Using CMake

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/diccionario_aed1 < 01-dictionary-trie-hashtable-cpp/tests/sample_input.txt
```
