//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;

long long int resultadosuma(long long int numero);

int main() {
	int num1;
	long long int numero, suma;
	cin >> num1;

	for (int i = 0; i < num1; i++) {

		cin >> numero;
		suma = resultadosuma(numero);
		cout << suma << endl;
	}
	return 0;
}

long long int resultadosuma(long long int numero) {
	long long int suma = 0;

	while (numero > 0) {

		suma = suma + numero % 10;
		numero = numero / 10;

	}
	return suma;
}