// LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;

const int filas = 100, columnas = 100;
typedef int tMatriz[filas][columnas];

void maxminFila(tMatriz cuadricula, int columnas, int& maxF, int& minF, int i);
void maxminColumna(tMatriz cuadricula, int filas, int& maxC, int& minC, int h);

int main() {
	int filas, columnas, carga;
	bool encontrado = false;
	tMatriz cuadricula;

	cin >> filas;
	cin >> columnas;

	while ((filas != 0) && (columnas != 0)) {

		for (int k = 0; k < filas; k++) {
			for (int w = 0; w < columnas; w++) {
				cin >> carga;
				cuadricula[k][w] = carga;
			}
		}

		int i = 0, h = 0, maxF, minF, maxC, minC;

		while (i < filas && !encontrado) {
			while (h < columnas && !encontrado) { 

				maxminFila(cuadricula, columnas, maxF, minF, i);
				maxminColumna(cuadricula, filas, maxC, minC, h);

				if (((cuadricula[i][h] == maxF) && (cuadricula[i][h] == minC)) || ((cuadricula[i][h] == minF) && (cuadricula[i][h] == maxC))) {
					encontrado = true;
				}

				h++;
			}
			h = 0;
			i++;
		}
		if (encontrado) {
			cout << "SI" << endl;
		}
		else cout << "NO" << endl;

		cin >> filas;
		cin >> columnas;
		encontrado = false;
	}
	return 0;
}

void maxminFila(tMatriz cuadricula, int columnas, int& maxF, int& minF, int i) {
	int minAux = cuadricula[i][0], maxAux = cuadricula[i][0];
	for (int cont = 0; cont < columnas; cont++) {
		if (cuadricula[i][cont] < minAux) {
			minAux = cuadricula[i][cont];
		}
		if (cuadricula[i][cont] > maxAux) {
			maxAux = cuadricula[i][cont];
		}
	}
	maxF = maxAux;
	minF = minAux;
}

void maxminColumna(tMatriz cuadricula, int filas, int& maxC, int& minC, int h) {
	int minAux = cuadricula[0][h], maxAux = cuadricula[0][h];
	for (int cont = 0; cont < filas; cont++) {
		if (cuadricula[cont][h] < minAux) {
			minAux = cuadricula[cont][h];
		}
		if (cuadricula[cont][h] > maxAux) {
			maxAux = cuadricula[cont][h];
		}
	}
	maxC = maxAux;
	minC = minAux;

}