# Module 02: Formal Algebraic Specifications of ADTs in Maude

This module contains 26 formal equational specifications written in **Maude** covering arithmetic from Peano axioms, linear data structures, set/multiset algebras, and self-balancing binary search trees (AVL rotations).

---

## Overview of Specification Files

### 1. [`specs/01-natural-numbers.maude`](./specs/01-natural-numbers.maude) (Exercises 101–107)
Constructs natural numbers from `cero` and the Peano successor operator `sucesor : N -> N`, along with error sorts (`NODEFINIDO`, `INFINITO`, `NEGATIVO`):
- **101–104**: `suma`, `esCero`, `esIgual`, `esDistinto`, `producto`, `potencia`, `cuadrado`, `factorial`, `predecesor`, `resta`, symmetric `diferencia`, `difUno`, total ordering (`esMenor`, `esMenorIgual`, `esMayor`, `esMayorIgual`), `maximo`, and `minimo`.
- **105–106**: Integer division (`division`), `modulo`, `mitad`, parity (`esPar`), base-2 integer `logaritmo`, and integer $n$-th root `raiz(n, m)` via candidate iteration (`sucRaiz`).
- **107**: Greatest Common Divisor (`mcd` via bounded divisor search `divisorComun`), Least Common Multiple (`mcm`), and coprimality test (`coprimos`).

### 2. [`specs/02-linear-structures.maude`](./specs/02-linear-structures.maude) (Exercises 110–118)
Defines an ordered alphabet `V` (`A < E < I < O < U`) and three foundational linear ADTs:
- **Stacks (`P`, 111–112)**: `pilaVacia`, `esVacia`, `push`, `pop`, `tope`, structural equality `esIgual`, bottom element retrieval `primero`, `tamano`, and occurrence counter `cuentaVocal`.
- **FIFO Queues (`C`, 113–114)**: `colaVacia`, `esVacia`, `meter`, recursive dequeue `sacar`, front inspection `cabecera`, batch insertion/removal (`meterVarias`, `sacarVarias`), `esIgual`, and `tamano`.
- **Lists (`L`, 115–118)**: `listaVacia`, `esVacia`, head `insertar`, tail `insertarFinal`, `tamano`, `primero`, `ultimo`, `cabeza` (all but last), `cola` (all but first), list reversal `invertir`, `concatenar`, `insertarVarias`, membership `pertenece`, lexicographical comparison `esMenor`, index search `buscar`, and $n$-th element lookup `posicion`.

### 3. [`specs/03-sets-and-bags.maude`](./specs/03-sets-and-bags.maude) (Exercises 120–126)
- **Sets (`C`, 120–122)**: `cjtoVacio`, `esVacio`, `insertar`, `esMiembro`, deduplicated `tamano`, `union`, `interseccion`, `diferencia`, `eliminar`, set equality via symmetric difference (`esVacio(diferencia(union(c, d), interseccion(c, d)))`), strict/non-strict inclusion (`esMenor`, `esMenorIgual`), and `disjuntos`.
- **Multisets / Bags (`B`, 125–126)**: `bolsaVacia`, `esVacia`, `insertar`, multiplicity counter `contar`, single-occurrence `eliminar`, additive `union`, minimum-multiplicity `interseccion`, `diferencia`, and multiset `esIgual`.

### 4. [`specs/04-binary-and-avl-trees.maude`](./specs/04-binary-and-avl-trees.maude) (Exercises 140–144)
Defines binary trees constructed via `arbolVacio : -> AB` and `construir : V AB AB -> AB`:
- **140–141**: `altura`, `numNodos`, structural `esIgual`, recursive BST order verification `esOrdenado`, `cuentaVocal`, `cuentaHojas`, and tree reflection `espejo`.
- **142–143**: Depth-first traversals returning lists (`preOrden`, `inOrden`, `postOrden`) and multiset extractors (`sacaTodos`, `sacaHojas`, level-order slice `sacaNivel`).
- **144 (AVL Balance & Rotations)**:
  - `esAVL`: Verifies $|h(L) - h(R)| \le 1$ recursively at every node.
  - `esPerfBal`: Verifies $|n(L) - n(R)| \le 1$ (weight-balanced binary tree).
  - **Single & Double AVL Rotations**:
    - `rsd` (Right-subtree single rotation / left rotation) & `rsi` (Left-subtree single rotation / right rotation).
    - `rdd` (Right-Left double rotation composed as `rsd(construir(v, a, rsi(b)))`) & `rdi` (Left-Right double rotation composed as `rsi(construir(v, rsd(a), b))`), with invalid rotation guard propagation (`ROTACIONNOVALIDA`).

## Collaborators

- **Marta Tomás** ([@MartaTR13](https://github.com/MartaTR13))
- **Pedro Villa** ([@pedro-villa](https://github.com/pedro-villa))
