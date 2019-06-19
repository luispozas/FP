//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;

int main() {
	int num1;
	long long int numero, suma, sumdef;
	cin >> num1;

	for (int i = 0; i < num1; i++) {
		suma = 0;
		cin >> numero;
		while (numero > 0) {

			suma = suma + numero % 10;
			numero = numero / 10;
		}
		if (suma <= 9) {
			cout << suma << endl;
		}

		if (suma > 9) {
			while (suma > 9) {
				sumdef = 0;
				while (suma > 0) {

					sumdef = sumdef + suma % 10;
					suma = suma / 10;
				}
			}
			cout << sumdef << endl;
		}
	}
	return 0;
}
