/* LUIS POZAS PALOMO */
#include <iostream>
#include <string>
using namespace std;

typedef struct {
	string nombre;
	int puntuacion;
	int distancia;
	int precio;
}tHotel;

typedef tHotel *tHotelPtr;

typedef struct {
	tHotelPtr *dinam;
	int tam, cap;
}tLista;

void OrdenarPorDistancia(tLista lista, int numHoteles);
void OrdenarPorPuntuacion(tLista lista, int numHoteles);
void OrdenarPorPrecio(tLista lista, int numHoteles);
void liberar(tLista& l);

int main() {
	int numHoteles;
	tLista lista, lista1, lista2, lista3;

	while (cin >> numHoteles) {
		lista.tam = 0;
		lista.cap = numHoteles;
		lista.dinam = new tHotelPtr[numHoteles];

		for (int i = 0; i < numHoteles; i++) {
			tHotelPtr aux = new tHotel;
			cin >> aux->nombre >> aux->puntuacion >> aux->distancia >> aux->precio;
			lista.dinam[i] = aux;
			lista.tam++;
		}

		lista1 = lista;
		OrdenarPorPuntuacion(lista1, numHoteles);
		lista2 = lista;
		OrdenarPorDistancia(lista2, numHoteles);
		lista3 = lista;
		OrdenarPorPrecio(lista3, numHoteles);

		liberar(lista);
	}

	return 0;
}

void liberar(tLista & l) {
	delete[] l.dinam;
	l.dinam = nullptr;
	l.tam = 0;
}

void OrdenarPorDistancia(tLista lista, int numHoteles) {
	//ORDENACION POR METODO DE LA BURBUJA:

	bool inter = true;
	int i = 0;
	while ((i < numHoteles - 1) && inter) {
		inter = false;
		for (int j = numHoteles - 1; j > i; j--) {
			if (lista.dinam[j]->distancia < lista.dinam[j - 1]->distancia) {
				tHotelPtr tmp;
				tmp = lista.dinam[j];
				lista.dinam[j] = lista.dinam[j - 1];
				lista.dinam[j - 1] = tmp;
				inter = true;
			}
			else if (lista.dinam[j]->distancia == lista.dinam[j - 1]->distancia) {
				if (lista.dinam[j]->nombre < lista.dinam[j - 1]->nombre) {
					tHotelPtr tmp1;
					tmp1 = lista.dinam[j];
					lista.dinam[j] = lista.dinam[j - 1];
					lista.dinam[j - 1] = tmp1;
				}
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}

	for (int i = 0; i < numHoteles; i++) {
		cout << lista.dinam[i]->nombre << " ";
	}
	cout << endl;
}

void OrdenarPorPuntuacion(tLista lista, int numHoteles) {
	//ORDENACION POR METODO DE LA BURBUJA:

	bool inter = true;
	int i = 0;
	while ((i < numHoteles - 1) && inter) {
		inter = false;
		for (int j = numHoteles - 1; j > i; j--) {
			if (lista.dinam[j]->puntuacion > lista.dinam[j - 1]->puntuacion) {
				tHotelPtr tmp;
				tmp = lista.dinam[j];
				lista.dinam[j] = lista.dinam[j - 1];
				lista.dinam[j - 1] = tmp;
				inter = true;
			}
			else if (lista.dinam[j]->puntuacion == lista.dinam[j - 1]->puntuacion) {
				if (lista.dinam[j]->nombre < lista.dinam[j - 1]->nombre) {
					tHotelPtr tmp1;
					tmp1 = lista.dinam[j];
					lista.dinam[j] = lista.dinam[j - 1];
					lista.dinam[j - 1] = tmp1;
				}
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}

	for (int i = 0; i < numHoteles; i++) {
		cout << lista.dinam[i]->nombre << " ";
	}
	cout << endl;
}

void OrdenarPorPrecio(tLista lista, int numHoteles) {
	//ORDENACION POR METODO DE LA BURBUJA:

	bool inter = true;
	int i = 0;
	while ((i < numHoteles - 1) && inter) {
		inter = false;
		for (int j = numHoteles - 1; j > i; j--) {
			if (lista.dinam[j]->precio < lista.dinam[j - 1]->precio) {
				tHotelPtr tmp;
				tmp = lista.dinam[j];
				lista.dinam[j] = lista.dinam[j - 1];
				lista.dinam[j - 1] = tmp;
				inter = true;
			}
			else if (lista.dinam[j]->precio == lista.dinam[j - 1]->precio) {
				if (lista.dinam[j]->nombre < lista.dinam[j - 1]->nombre) {
					tHotelPtr tmp1;
					tmp1 = lista.dinam[j];
					lista.dinam[j] = lista.dinam[j - 1];
					lista.dinam[j - 1] = tmp1;
				}
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}

	for (int i = 0; i < numHoteles; i++) {
		cout << lista.dinam[i]->nombre << " ";
	}
	cout << endl;
}