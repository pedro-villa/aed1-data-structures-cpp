#include <iostream>
#include <string>
#include <list>
#include "TablaHash.h"
using namespace std;

/*int hashmio(string str) {
    unsigned int hashValue = 5381;

    for (char c : str) {
        hashValue = ((hashValue << 5) + hashValue) + (char)(c); // hash * 33 + c
    }
	
    return hashValue%TAM;
}*/
int hashmio(string str){
	if (str.empty()) return 0;
	return (unsigned char)str[0] % TAM;
}

TablaHash::TablaHash(){
	nElem = 0;
}

void TablaHash::vaciar(){
	nElem = 0;
	for(int i=0;i<TAM;i++){
		T[i].clear();
	}
}
void TablaHash::insertar(string palabra){
	int A = hashmio(palabra);
	list<string>::iterator EA = T[A].begin();
	while(EA != T[A].end() && *EA < palabra){
		EA++;
	}
	if(EA == T[A].end() || *EA != palabra){
		T[A].insert(EA,palabra);
		nElem++;
	}
}
bool TablaHash::consultar(string palabra){
	int A = hashmio(palabra);
	list<string>::iterator EA = T[A].begin();
	while(EA != T[A].end() && *EA < palabra){
		EA++;
	}
	return (EA != T[A].end() && *EA == palabra);
}
void TablaHash::sacoPalabras(string i, string f){
	if(f <= i){
		return;
	}
	
	else {
		int hashi = hashmio(i);
		int hashf = hashmio(f);
		if(hashi==hashf){
			list<string>::iterator EA = T[hashi].begin();
			while(EA != T[hashi].end() && *EA<=i){
				EA++;
			}
			while(EA != T[hashi].end() && *EA<f){
				cout<<*EA<<" ";
				EA++;
			}
		}
		else {
			for(int e=hashi;e<=hashf;e++){
				list<string>::iterator EA = T[e].begin();
				if(e==hashi){
					while(EA != T[e].end() && *EA<=i){
						EA++;
					}
					while(EA != T[e].end()){
						cout<<*EA<<" ";
						EA++;
					}
				}
				else if(e==hashf){
					while(EA != T[e].end() && *EA<f){
						cout<<*EA<<" ";
						EA++;
					}
				}
				else{
					while(EA != T[e].end()){
						cout<<*EA<<" ";
						EA++;
					}
				}
			}
		}
	}
}
