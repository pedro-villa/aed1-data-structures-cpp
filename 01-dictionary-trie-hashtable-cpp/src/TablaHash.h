#ifndef TABLAHASH
#define TABLAHASH

#include <iostream>
#include <list>
#include <string>

using namespace std;

const int TAM = 256;

class TablaHash {
  private:
  	 list<string> T[TAM];
     int nElem;
  public:
     TablaHash ();
     void insertar (string palabra);
     bool consultar (string palabra);
     void vaciar (void);
     int devolver (void) { return nElem; }
     void sacoPalabras(string i,string f);
};

#endif
