#include <iostream>
#include <list>
#include <algorithm>
#include "arbolTrie.h"

using namespace std;


Nodo::Nodo(char caracter){
	valor = caracter;
	finDePalabra = false;
	altura = 0;
	siguiente = NULL;
	hijo = NULL;
}

// A LA enie le hacemos ser la { y a la u dieresis el caracter |
// luego nos preocupamos de cambiarlas.

int Trie::devolver(){
	return nElem;
}

Trie::Trie() {
    raiz = new Nodo(' '); 
    nElem = 0;
}

void liberarNodos(Nodo* nodo) {
    if (nodo == NULL) return;

    while (nodo != NULL) {
        Nodo* siguienteNodo = nodo->siguiente;
        liberarNodos(nodo->hijo); 
        delete nodo; 
        nodo = siguienteNodo; 
    }
}

Trie::~Trie() {
    liberarNodos(raiz);
}

void Trie::vaciar() {
    liberarNodos(raiz->hijo); 
    raiz->siguiente = NULL; 
    raiz->hijo = NULL; 
    raiz->altura = 0; 
    nElem = 0;
}

void imprimirDesconvertir(string convertido){
	string sol;
	for(size_t i=0;i<convertido.size();i++){
		if(convertido[i] == '{'){
			sol+=(char)0xC3;
			sol+=(char)0x91;
		}
		else if(convertido[i] == '|'){
			sol+=(char)0xC3;
			sol+=(char)0x9C;
		}
		else{
			sol+=convertido[i];
		}
		
	}
	cout<<sol;
}

string convertir(string palabra){ // cambio las enie por { y las u dieresis por |
	string sol;
	for(size_t i=0;i<palabra.size();i++){
		if((char)palabra[i] == (char)0xC3){
			
			int num = (char)palabra[i+1];
			if(num == (char)0x91){
				sol += '{';
			}
			if(num == (char)0x9C){
				sol += '|';
			}	
			i++;
		}
		else{
			sol+=palabra[i];
		}
	}
	return sol;
}


Nodo* buscaOCreaNodo(Nodo *nodo, char c){
	
	Nodo* actual = nodo;
	while(actual->siguiente != NULL && actual->siguiente->valor < c){
		
        actual = actual->siguiente;
	}
	if(actual->siguiente != NULL){
		if(actual->siguiente->valor == c){
			return actual->siguiente;
		}
		else{
			Nodo *nuevo = new Nodo(c);
			nuevo->siguiente = actual->siguiente;
			actual->siguiente = nuevo;
			Nodo *nuevo2 = new Nodo(' ');
			nuevo->hijo = nuevo2;
			return nuevo;
		}
	}
	else{
		
		Nodo *nuevo = new Nodo(c);
		actual->siguiente = nuevo;
		Nodo *nuevo2 = new Nodo(' ');
		nuevo->hijo = nuevo2;
		return nuevo;
	}
}

void Trie::insertar(string str) {
    Nodo* actual = raiz;
    string palabra = convertir(str);
    for (size_t i = 0; i < palabra.size(); i++) {
    	
        char c = palabra[i];
        //Busco el nodo hijo con el caracter
        
        int longitudRestante = (int)(palabra.size() - i);
        
        actual = buscaOCreaNodo(actual,c);
        actual->altura = max(actual->altura, longitudRestante);
        actual = actual->hijo;
        
    }
    if(actual->valor != '$'){
    	actual->valor = '$';
    	nElem++;
	}
    
    actual->finDePalabra = true;
}

Nodo* buscaNodoEnNivel(Nodo* nodo, char c) {

    Nodo* actual = nodo->siguiente;
    while (actual != NULL) {

        if (actual->valor == c) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

bool Trie::buscar(string str) {
    Nodo* actual = raiz;
    string palabra = convertir(str);
    for (size_t i = 0; i < palabra.size(); i++) {
        char c = palabra[i];
        Nodo* buscado = buscaNodoEnNivel(actual,c);
        if(buscado == NULL){
        	return false;
		}
        actual = buscado->hijo;
    }
	// Comprobar el nodo final para el carácter especial que indica fin de palabra
    
	return actual->valor == '$' && actual->finDePalabra;
}

Nodo* nodoConMayorAltura(Nodo* nodo) {
    Nodo* actual = nodo->siguiente;
    Nodo* nodoMayorAltura = NULL;
    int maxAltura = -1;

    while (actual != NULL) {
        if (actual->altura > maxAltura) {
            maxAltura = actual->altura;
            nodoMayorAltura = actual;
        }
        actual = actual->siguiente;
    }

    return nodoMayorAltura;
}

void Trie::alarga(string str) {
    Nodo* actual = raiz;
	string prefijo = convertir(str);
    // Buscar el nodo que corresponde al último carácter del prefijo
    for (size_t i = 0; i < prefijo.size(); i++) {
        char c = prefijo[i];
        actual = buscaNodoEnNivel(actual, c);
        if (actual == NULL) {
            return;
        }
        actual = actual->hijo; // Descender al siguiente nivel
    }

    // Construir la palabra más larga desde este nodo
    string palabraMasLarga = prefijo;
    while (actual != NULL) {
        Nodo* nodoLargo = nodoConMayorAltura(actual);
        if (nodoLargo == NULL) {
            break;
        }
        palabraMasLarga+=nodoLargo->valor;
        actual = nodoLargo->hijo;
    }
    cout<<" ";
    imprimirDesconvertir(palabraMasLarga);
    
}
