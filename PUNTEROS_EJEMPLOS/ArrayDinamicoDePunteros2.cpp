// Autora: Sonia Est�vez Mart�n
// C�digo para explicar en clase, curso 2017-18
// Array din�mico de punteros
// con tama�o inicial del array determinado por el usuario

#include <iostream>
#include <string>
#include "checkML.h"
using namespace std;

typedef struct{
	string nombre;
	int unidades;
}tObjeto;

// Puntero a un objeto
typedef tObjeto *tObjPtr;

// Array din�mico de punteros a objetos
typedef struct{
	tObjPtr *dinam;
	int tam, capacidad;
}tLista;


//Prototipos
void ampliar(tLista & l);
void addElem(tLista & l);
void liberar(tLista & l);
void visualizar(const tLista & l);
int menu();
int buscarElemento(const tLista & l, const string & s);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tObjeto obj;
	tLista lista;

	// Primero pedimos el tama�o del array
	int tam_inicial = 0;
	cout << "Dime el tama�o inicial que deseas dar a la lista " << endl;
	cin >> tam_inicial;

	// Segundo reservamos la memoria inicial
	lista.capacidad = tam_inicial;
	lista.dinam = new tObjPtr[tam_inicial];
	lista.tam = 0;

	int opcion = menu();
	while (opcion != 0){
		switch (opcion) {
		case 1:
		{
				  addElem(lista);
		}
			break;
		case 2:
		{
				  visualizar(lista);
		}
			break;
		case 3:
		{
				  string name = "";
				  cout << "Introduce el elemento a buscar su posici�n en la lista" << endl;
				  cin >> name;
				  int pos = buscarElemento(lista, name);
				  if (pos == -1){
					  cout << "No lo he encontrado, :-(" << endl;
				  }
				  else{
					  cout << "Est� en la pocici�n " << pos << endl;
				  }
		}
			break;
		}
		opcion = menu();

	}
	liberar(lista);
	return 0;
}

void liberar(tLista & l){
	for (int i = 0; i < l.tam; i++){
		delete l.dinam[i];
	}
	delete[] l.dinam;
	l.dinam = nullptr;
	l.tam = 0;
}


int buscarElemento(const tLista & l, const string & s){
	int pos = 0;
	bool encontrado = false;

	while (pos < l.tam && !encontrado){
		if (l.dinam[pos]->nombre == s){
			encontrado = true;
		}
		else{
			pos++;
		}
	}
	if (!encontrado){
		pos = -1;
	}
	return pos;
}

int menu() {
	int op = -1; // Cualquiera no v�lida
	while ((op < 0) || (op > 4)) {
		cout << "  1 - Nuevo objeto" << endl;
		cout << "  2 - Visualizar lista" << endl;
		cout << "  3 - Buscar en la lista" << endl;
		cout << "  0 - Salir" << endl;
		cout << "  Opci�n: ";
		cin >> op;
		if ((op < 0) || (op > 2)) {
			cout << "  �Opci�n no v�lida!" << endl;
		}
		cout << endl;
	}
	return op;
}

void ampliar(tLista & l){
	//Duplica el tama�o
	tObjPtr * aux = nullptr;

	aux = new tObjPtr[2 * l.capacidad];
	for (int i = 0; i < l.tam; i++)
	{
		aux[i] = l.dinam[i];
	}
	delete[] l.dinam; //OJO! Memoria -> [] para listaes
	l.dinam = aux;
	l.capacidad *= 2;
	aux = nullptr;
}


void addElem(tLista & l){


	if (l.capacidad == l.tam){
		ampliar(l);
	}

	//INSERTA UN NUEVO ELEMENTO
	// Pide los datos

	l.dinam[l.tam] = new tObjeto;

	cout << "Introduce un nombre (sin espacios) y un n�mero" << endl;
	cin >> l.dinam[l.tam]->nombre >> l.dinam[l.tam]->unidades;
	l.tam++;
}


void visualizar(const tLista & l){
	for (int i = 0; i< l.tam; i++){
		cout << "          Elemento " << i << ": " << l.dinam[i]->nombre << " " << l.dinam[i]->unidades << endl;
	}
	cout << endl;
}