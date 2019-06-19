// LUIS POZAS
#include <iostream>
#include <string>
using namespace std;

const int filas = 100, columnas = 100;
typedef int tMatriz[filas][columnas];


int main() {
	int filasa, columnasa, filasb, columnasb, carga, mult = 0, suma = 0;
	tMatriz a, b;

	// CARGO LAS MATRICES
	while (cin >> filasa >> columnasa) {
		for (int i = 0; i < filasa; i++) {
			for (int j = 0; j < columnasa; j++) {
				cin >> carga;
				a[i][j] = carga;

			}
		}
		cin >> filasb;
		cin >> columnasb;
		for (int i = 0; i < filasb; i++) {
			for (int j = 0; j < columnasb; j++) {
				cin >> carga;
				b[i][j] = carga;

			}
		}

	// REALIZO LA MULTIPLICACION
		for (int i = 0; i < filasa; i++) {
			for (int j = 0; j < columnasb; j++) {
				for (int k = 0; k < columnasa; k++) {

					mult = a[i][k] * b[k][j];
					suma = suma + mult;

				}
				cout << suma << " ";
				suma = 0;
				mult = 0;
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}