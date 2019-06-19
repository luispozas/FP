//LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;

const int filas = 99, columnas = 99;
typedef int tMatriz[filas][columnas];

void alturayposicion(const tMatriz cuadricula, const int filas, const int columnas, int& posf, int& posc, int& valormax);

int main() {
	int filas, columnas, carga, posf = 0, posc = 0, valormax = 0;
	tMatriz cuadricula;

	while (cin >> filas >> columnas) {

		for (int k = 0; k < filas; k++) {
			for (int w = 0; w < columnas; w++) {
				cin >> carga;
				cuadricula[k][w] = carga;
			}
		}

		alturayposicion(cuadricula, filas, columnas, posf, posc, valormax);

		cout << valormax << " " << posf << " " << posc << endl;
	}
	return 0;
}

void alturayposicion(const tMatriz cuadricula, const int filas, const int columnas, int& posf, int& posc, int& valormax) {
	posf = 0;
	posc = 0;

	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {

			if (i == 0 && j == 0) {
				valormax = cuadricula[i][j];
			}
			if (cuadricula[i][j] > valormax) {
				valormax = cuadricula[i][j];
				posf = i;
				posc = j;
			}
		}
	}
}