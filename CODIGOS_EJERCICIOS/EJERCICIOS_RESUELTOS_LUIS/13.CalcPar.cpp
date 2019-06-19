//Luis Pozas y Pablo Alvarez

#include <iostream>
#include <string>
using namespace std;

int main() {

	int a;
	int numero1, numero2, acumula;
	char caracter;
	cin >> a;

	for (int i = 0; i < a; i++) {
		cin >> numero1 >> caracter;
		acumula = numero1;
		while (caracter != '.') {

			cin >> numero2;

			if (caracter == '+') {
				acumula = acumula + numero2;
				cout << acumula;
			}
			if (caracter == '-') {
				acumula = acumula - numero2;
				cout << acumula;
			}

			cin >> caracter;

			if (caracter != '.') {
				cout << ", ";
			}
			else cout << endl;
		}
	}
return 0;
}