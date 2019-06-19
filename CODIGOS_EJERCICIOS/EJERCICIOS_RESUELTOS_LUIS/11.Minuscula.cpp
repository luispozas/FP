//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;

int main() {

	int num1;
	char texto;

	cin >> num1;
	cin.ignore();

	for (int i = 0; i < num1; i++) {
		cin.get(texto);
		while (texto != '\n') {
			texto = tolower(texto);
			cout << texto;
			cin.get(texto);
		}
		if (texto = '\n') {
			cout << endl;
		}
	}
	return 0;
}
