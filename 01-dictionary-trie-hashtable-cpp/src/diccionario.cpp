#include <list>
#include "diccionario.h"
using namespace std;

DicPalabras::DicPalabras(){
	
}
void DicPalabras::vaciar(){
	arbol.vaciar();
	tabla.vaciar();
}
void DicPalabras::insertar(string cadena){
	arbol.insertar(cadena);
	tabla.insertar(cadena);
}
bool DicPalabras::consultar(string palabra){
	return arbol.buscar(palabra);
}
void DicPalabras::alarga(string palabra){
	arbol.alarga(palabra);
}
void DicPalabras::saco(string i, string f){
	tabla.sacoPalabras(i, f);
}
