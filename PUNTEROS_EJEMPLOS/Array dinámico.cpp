#include <iostream>
#include <string>
#include "checkML.h"
using namespace std;
const int TAM_INICIAL = 3;

typedef struct{
	string nombre;
	int unidades;
}tObjeto;

// Array dinámico de objetos
typedef struct{
	tObjeto *dinam;
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

	//Primero reservamos la memoria inicial
	lista.capacidad = TAM_INICIAL;
	lista.dinam = new tObjeto[TAM_INICIAL];
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
				  cout << "Introduce el elemento a buscar su posición en la lista" << endl;
				  cin >> name;
				  int pos = buscarElemento(lista, name);
				  if (pos == -1){
					  cout << "No lo he encontrado, :-(" << endl;
				  }
				  else{
					  cout << "Está en la pocición " << pos << endl;
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
	delete[] l.dinam;
	l.dinam = nullptr;
	l.tam = 0;
}


int buscarElemento(const tLista & l, const string & s){
	int pos = 0;
	bool encontrado = false;

	while (pos < l.tam && !encontrado){
		if (l.dinam[pos].nombre == s){
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
	int op = -1; // Cualquiera no válida
	while ((op < 0) || (op > 4)) {
		cout << "  1 - Nuevo objeto" << endl;
		cout << "  2 - Visualizar lista" << endl;
		cout << "  3 - Buscar en la lista" << endl;
		cout << "  0 - Salir" << endl;
		cout << "  Opción: ";
		cin >> op;
		if ((op < 0) || (op > 2)) {
			cout << "  ¡Opción no válida!" << endl;
		}
		cout << endl;
	}
	return op;
}

void ampliar(tLista & l){
	//Duplica el tamaño
	tObjeto * aux = nullptr;

	aux = new tObjeto[2 * l.capacidad];
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

	tObjeto obj;

	cout << "Introduce un nombre (sin espacios) y un número" << endl;
	cin >> obj.nombre >> obj.unidades;
	l.dinam[l.tam] = obj;
	l.tam++;
}


void visualizar(const tLista & l){
	for (int i = 0; i< l.tam; i++){
		cout << "          Elemento " << i << ": " << l.dinam[i].nombre << " " << l.dinam[i].unidades << endl;
	}
	cout << endl;
}