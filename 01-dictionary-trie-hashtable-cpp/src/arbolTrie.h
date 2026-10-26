// Trie.h
#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <list>
#include <string>

using namespace std;

class Nodo {
public:
    char valor;
    bool finDePalabra;
    Nodo* siguiente;
    Nodo* hijo;
    int altura;

    Nodo(char valor);
};

class Trie {
private:
    Nodo* raiz; 
	int nElem;
public:
    Trie();
    ~Trie();
    void insertar(string palabra);
    bool buscar(string palabra);
    void alarga(string palabra);
    void vaciar();
    int devolver();
};

#endif // TRIE_H
