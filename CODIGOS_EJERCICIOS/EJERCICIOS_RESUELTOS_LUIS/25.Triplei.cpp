//LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;

const int MAX = 10000;
typedef int tArray[MAX];

int main() {
	int numcasos, num1, numsec, w = 0;
	tArray secuencia;
	bool encontrado = false;

	cin >> numcasos;
	for (int i = 0; i < numcasos; i++) {
		cin >> num1;
		for (int j = 0; j < num1; j++) {
			cin >> numsec;
			secuencia[j] = numsec;
		}
		while ((w < num1) && (!encontrado)) {
			if ((secuencia[w] % 2 != 0) && (secuencia[w] % 3 == 0)) {
				cout << "Si" << " " << secuencia[w] << endl;
				encontrado = true;
			}
			w++;
		}
		if ((w == num1) && (!encontrado)) {
			cout << "No" << endl;
		}
		w = 0;
		encontrado = false;
	}
	return 0;
}