//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;

const int numero = 10000;
typedef int tNumero[numero];

int main() {
	int num1, contador;
	long long int numero;
	tNumero par;
	cin >> num1;

	for (int i = 0; i < num1; i++) {
		cin >> numero;
		contador = 0;
		for (int j = 0; j < numero; j++) {

			cin >> par[j];

			if (par[j] % 2 == 0) {
				contador++;
			}
		}
		cout << contador << endl;
	}
	return 0;
}