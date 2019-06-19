//Luis Pozas y Pablo Alvarez
#include <iostream>
#include <string>
using namespace std;

void estaOrdenada(string palabra);

int main() {
	string palabra;
	cin >> palabra;

	while (palabra != "XXX") {
		(estaOrdenada(palabra));
		cin >> palabra;
	}
	return 0;
}

void estaOrdenada(string palabra) {
	int contador1 = 0, contador2 = 0;
	int i = 0, num1;

	cout << palabra.size() << " ";
	num1 = palabra.size() - 1;

	while ( i < num1) {
		if (palabra[i] < palabra[i + 1]) {
			contador1++;
		}
		else { contador1 = 0; }

		if (contador1 >= contador2) {
			contador2 = contador1;
		}
		i++;
	}
	cout << contador2 + 1 << endl;
}
