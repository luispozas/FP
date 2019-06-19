//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;

int main() {
	int num1, muestra;
	long long int numero;
	cin >> num1;

	for (int i = 0; i < num1; i++) {
		cin >> numero;
		while (numero > 0) {
			muestra = numero % 10;
			numero = numero / 10;
			cout << muestra;
		}
		if (numero = 0) {
			cout << endl << endl;
		}
		cout << endl;
	}
	return 0;
}