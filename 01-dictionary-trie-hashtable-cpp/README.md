# Module 01: C++ Dictionary Engine — LCRS Multiway Trie & Chained Hash Table

This module implements an interactive Spanish lexical dictionary and word-game query engine in C++17 (`004final.cpp`, `diccionario`, `arbolTrie`, `TablaHash`).

---

## 1. Left-Child Right-Sibling (LCRS) Multiway Trie (`arbolTrie.h`, `arbolTrie.cpp`)

### 1.1. Memory Layout & Pointer Representation
A naive multiway Trie over a byte alphabet allocates an array of 256 pointers in every node ($256 \times 8 = 2048\text{ bytes}$ on 64-bit architectures), resulting in severe internal fragmentation when most nodes have only 1–3 children.

To minimize memory footprint, `Trie` represents the multiway tree as a binary pointer structure using the **Left-Child Right-Sibling (LCRS)** representation:
- `Nodo* hijo`: Points to the dummy header node (`' '` or `'$'` if the prefix ending at the parent is a complete dictionary word) of the child level.
- `Nodo* siguiente`: Points to the next sibling character at the same depth, maintained in **strictly ascending lexicographical order** (`actual->siguiente->valor < c`).
- `int altura`: Stores the length of the longest word suffix reachable from this node downwards.

```text
[raiz: ' '] ──siguiente──► ['A' | altura=6] ──siguiente──► ['C' | altura=10]
                             │                               │
                            hijo                            hijo
                             ▼                               ▼
                           [' '] ──siguiente──► ['G'...]   [' '] ──siguiente──► ['A' | altura=9]
```

### 1.2. Height-Augmented Prefix Autocompletion (`Trie::alarga`)
Given a prefix $P$, the `<alarga>` command finds the longest dictionary word starting with $P$ (breaking ties alphabetically):
1. **Prefix Traversal**: Descend from `raiz` along the characters of $P$ in $O(|P| \cdot |\Sigma|)$ time via `buscaNodoEnNivel`.
2. **Height-Guided Greedy Descent**: Because every node records the exact maximum suffix length `altura` updated during insertion (`actual->altura = max(actual->altura, longitudRestante)`), `Trie::alarga` does not need to perform a DFS/BFS over the subtree. At each level, `nodoConMayorAltura` selects the first sibling maximizing `altura` (since siblings are sorted alphabetically, strict inequality `actual->altura > maxAltura` automatically breaks ties in favor of the lexicographically smallest word).

---

## 2. Low-Level UTF-8 Normalization & 1-Byte Sentinel Compaction

Spanish words contain multi-byte UTF-8 characters (lead byte `0xC3` followed by continuation byte `0x81`–`0xBC`). Storing raw 2-byte sequences directly in a character-per-node Trie would split a single letter across two tree levels and corrupt word length (`altura`) calculations.

The engine resolves this in two stages:
1. **Input Folding (`modificar` in `004final.cpp`)**:
   - Inspects raw byte pairs starting with `0xC3`:
     - Accented vowels (`á, é, í, ó, ú` and `Á, É, Í, Ó, Ú`) are folded into single-byte uppercase ASCII (`'A', 'E', 'I', 'O', 'U'`).
     - `ñ`/`Ñ` (`0xC3 0xB1` / `0xC3 0x91`) is normalized to uppercase UTF-8 `Ñ` (`0xC3 0x91`).
     - `ü`/`Ü` (`0xC3 0xBC` / `0xC3 0x9C`) is normalized to uppercase UTF-8 `Ü` (`0xC3 0x9C`).
2. **Internal 1-Byte Trie Encoding (`convertir` / `imprimirDesconvertir` in `arbolTrie.cpp`)**:
   - Before traversing the Trie, `convertir()` maps the 2-byte sequence `Ñ` (`0xC3 0x91`) to `'{'` (ASCII `0x7B`) and `Ü` (`0xC3 0x9C`) to `'|'` (ASCII `0x7C`).
   - Before printing results, `imprimirDesconvertir()` restores `'{'` $\rightarrow$ `Ñ` and `'|'` $\rightarrow$ `Ü`.

---

## 3. Separate-Chaining Hash Table (`TablaHash.h`, `TablaHash.cpp`)

`TablaHash` partitions words into $B = 256$ buckets indexed by their leading unsigned byte (`(unsigned char)str[0] % TAM`), maintaining each bucket `std::list<string> T[TAM]` in ascending lexicographical order:
- **Duplicate-Free Insertion (`insertar`)**: Scans the bucket until `*EA >= palabra` and inserts only if `*EA != palabra`.
- **Early-Exit Lookup (`consultar`)**: Stops scanning a bucket as soon as `*EA >= palabra`.
- **Lexicographical Range Query (`sacoPalabras` / `<saco> w1 w2`)**: Exploits the order-preserving first-byte bucket index to iterate only across buckets `hashmio(w1) .. hashmio(w2)` and emit all words $w$ satisfying $w_1 < w < w_2$.
