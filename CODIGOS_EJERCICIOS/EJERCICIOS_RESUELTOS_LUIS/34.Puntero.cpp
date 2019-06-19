//Luis Pozas Palomo
#include <iostream>
#include <string>

using namespace std;

const int N = 200;

typedef struct {
	string titulo;
	string tema;
} tFoto;

typedef tFoto *tFotoPtr;
typedef tFotoPtr tArray[N];

typedef struct {
	tArray dinam;
	int tam;
} tLista;

void liberar(tLista & l);

int main() {
	tLista lista1, lista2;
	int cont;
	string basura;

	cin >> cont;
	getline(cin, basura);

	while (cont != 0) {
		lista1.tam = 0;
		lista2.tam = 0;
		for (int i = 0; i < cont; i++) {
			lista1.dinam[i] = new tFoto;
			getline(cin, lista1.dinam[i]->titulo);
			lista1.tam++;
			lista2.dinam[i] = lista1.dinam[i];
			lista2.tam++;
		}

		for (int i = 0; i < cont; i++) {
			getline(cin, lista1.dinam[i]->tema);
		}

		//BURBUJA:

		for (int i = 0; i < lista1.tam - 1; i++) {
			for (int j = lista1.tam - 1; j > i; j--) {
				if (lista1.dinam[j]->titulo < lista1.dinam[j - 1]->titulo) {
					tFoto *tmp = lista1.dinam[j];
					lista1.dinam[j] = lista1.dinam[j - 1];
					lista1.dinam[j - 1] = tmp;
				}
			}
		}

		for (int i = 0; i < cont; i++) {
			cout << lista1.dinam[i]->titulo << endl;
		}
		cout << endl;

		for (int i = 0; i < lista1.tam - 1; i++) {
			for (int j = lista1.tam - 1; j > i; j--) {
				if ((lista2.dinam[j]->tema < lista2.dinam[j - 1]->tema) || ((lista2.dinam[j]->tema == lista2.dinam[j - 1]->tema) && (lista2.dinam[j]->titulo < lista2.dinam[j - 1]->titulo))) {
					tFoto *tmp = lista2.dinam[j];
					lista2.dinam[j] = lista2.dinam[j - 1];
					lista2.dinam[j - 1] = tmp;
				}
			}
		}

		for (int i = 0; i < cont; i++) {
			cout << lista2.dinam[i]->tema << " - " << lista2.dinam[i]->titulo << endl;
		}
		cout << endl;

		cin >> cont;
		getline(cin, basura);

	}
	return 0;
}

