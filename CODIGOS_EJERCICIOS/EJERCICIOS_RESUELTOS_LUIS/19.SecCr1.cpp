//Luis Pozas y Pablo Alvarez

#include <iostream>
#include <string>
using namespace std;

bool estaOrdenada(string palabra);

int main() {
	bool ordenada;
	string palabra;
	cin >> palabra;

	while (palabra != "XXX") {
		ordenada = (estaOrdenada(palabra));

		if (ordenada == true) {
			cout << "SI" << endl;
		}
		else if (ordenada == false) {
			cout << "NO" << endl;
		}
		cin >> palabra;
	}
	return 0;
}

bool estaOrdenada(string palabra) { //Devuelve un bool para identificar si esta ordenada 
	bool resultado = true;
	for (int i = 0; i < palabra.size() - 1; i++) {
		if (palabra[i] >= palabra[i + 1]) {
			resultado = false;
			i = palabra.size();
		}
	}
	return resultado;
}
	
