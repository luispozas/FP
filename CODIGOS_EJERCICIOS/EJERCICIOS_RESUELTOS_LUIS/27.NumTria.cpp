//LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;

int main() {
	int num1, aux = 0, j = 1;
	bool encontrado = false;

	cin >> num1;

	while (num1 != 0) {
		while ((!encontrado) && (j <= num1)) {
			aux = aux + j;
			if (aux == num1) {
				encontrado = true;
				cout << num1 << endl;
			}
			j++;
		}
		cin >> num1;
		j = 1;
		encontrado = false;
		aux = 0;
	}
	return 0;
}