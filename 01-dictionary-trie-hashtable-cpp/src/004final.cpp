#include <iostream>
#include <string>
#include "diccionario.h"
using namespace std;

DicPalabras diccionario;

string modificar(string a){
	string b;

	for(unsigned int i=0;i<a.length();i++){
		if((int)a[i] >= 97 && (int)a[i]<=122){
			b += toupper(a[i]);
		}
		else if((char)a[i] == (char)0xC3){

			switch ((char)a[i+1]) {

            	case (char)0xA1 :  b+='A';break;
            	case (char)0xA9 :  b+='E';break;
            	case (char)0xAD :  b+='I';break;
            	case (char)0xB3 :  b+='O';break;
            	case (char)0xBA :  b+='U';break;
            	case (char)0xBC :  b+=(char)0xC3;b+=(char)0X9C;break;
            	case (char)0XB1 :  b+=(char)0xC3;b+=(char)0X91;break;
            	case (char)0x81 :  b+='A';break;
            	case (char)0x89 :  b+='E';break;
            	case (char)0x8D :  b+='I';break;
            	case (char)0x93 :  b+='O';break;
            	case (char)0x9A :  b+='U';break;
            	case (char)0x9C :  b+=(char)0xC3;b+=(char)0X9C;break;
            	case (char)0x91 :  b+=(char)0xC3;b+=(char)0X91;break;
            	default: b+=(char)0xC3;b+= a[i+1];

			}
			i++;
        }
        else{
        	b+=a[i];
		}

	}
	return b;
}
void INSERTAR(){
	string str;
	int nPalabras=0;
	while( cin>>str && str != "</insertar>"){
		nPalabras++;
		diccionario.insertar(modificar(str));
	}
	cout<<"Insertando: "<<nPalabras<<" palabras"<<endl;
	cout<<"Total diccionario: "<<diccionario.numElem()<<" palabras"<<endl;
}
void VACIAR(){
	diccionario.vaciar();
	cout<<"Vaciando"<<endl;
	cout<<"Total diccionario: 0 palabras"<<endl;
}
void BUSCAR(){
	string str;
	cin>>str;
	cout<<"Buscando: "<<modificar(str)<<" -> ";
	if(diccionario.consultar(modificar(str))){
        	cout<<"Encontrada"<<endl;
	}
	else{
        	cout<<"No encontrada"<<endl;
	}
}
void PARTIDAS(){
	string str;
	cout<<"Partidas:" << modificar(str);
	while(str != "</partidas>"){
		cin >> str;
		if(str != "</partidas>")
		cout<< " " << modificar(str);
	}
	cout<<endl;
	cout<<"No implementado"<<endl;
}
void ALOCADO(){
	string str;
	cin>>str;
	cout<<"Alocado: "<<modificar(str)<<endl;
	cout<<"No implementado"<<endl;
}
void CESAR(){
    string str;
    cin >> str;
    cout << "César: " << modificar(str) << endl << "No implementado" << endl;
}

void JUANAGRAMA(){
    string str;
    cin >> str;
    cout << "Juanagrama: " << modificar(str) << endl << "No implementado" << endl;
}

void SACO(){
    string str, str2;
    cin >> str;
    cin >> str2;
    cout << "Saco: " << modificar(str) << " " << modificar(str2) << " -> ";
    diccionario.saco(modificar(str), modificar(str2));
    cout << endl;
}

void CONSOME(){
    string str;
    cin >> str;
    cout << "Consomé: " << modificar(str) << endl << "No implementado" << endl;
}

void ALARGAPALABRAS(){
    string str;
    cin >> str;
    cout<<"Alarga: "<<modificar(str)<<" ->";
	diccionario.alarga(modificar(str));
	cout<<endl;
}

void EXIT(){
    cout << "Saliendo..." << endl;
    exit(0);
}
void interprete(string comando){

	if(comando == "<insertar>"){
		INSERTAR();
	}
	if(comando == "<vaciar>"){
		VACIAR();
	}
	if(comando == "<buscar>"){
		BUSCAR();
	}
	if(comando == "<partidas>"){
		PARTIDAS();
	}
	if(comando == "<alocado>"){
		ALOCADO();
	}
	if(comando == "<césar>"){
		CESAR();
	}
	if(comando == "<juanagra>"){
		JUANAGRAMA();
	}
	if(comando == "<saco>"){
		SACO();
	}
	if(comando == "<consomé>"){
		CONSOME();
	}
	if(comando == "<alarga>"){
		ALARGAPALABRAS();
	}
	if(comando == "<exit>"){
		EXIT();
	}



}

int main(){

	string str;
	while(cin>>str){
		interprete(str);
	}
	return 0;
}
