#ifndef DICCIONARIO
#define DICCIONARIO

#include "TablaHash.h"
#include "arbolTrie.h"
#include <iostream>
#include <string>
using namespace std;

class DicPalabras{
   private:
 	Trie arbol;
 	TablaHash tabla;
   public:
 	DicPalabras ();
 	void vaciar ();
 	void insertar (string palabra);
 	bool consultar (string palabra);
 	int numElem (void) {return arbol.devolver();}
	void alarga(string str);
	void saco(string i, string f);
};

#endif
