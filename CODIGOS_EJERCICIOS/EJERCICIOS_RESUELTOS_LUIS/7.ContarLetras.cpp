//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;


int main()
{
	char texto, caracter;
	int num1, contador1, contador2;

	cin >> num1;
	cin.ignore();
	for (int i = 0; i < num1; i++) {


		contador1 = 0;
		contador2 = 0;

		caracter = cin.get();
		caracter = tolower(caracter);
		cin.ignore();
		texto = cin.get();

		while (texto != '\n') {

			texto = tolower(texto);

			if (texto == caracter) {

				contador1++;
			}

			contador2++;


			texto = cin.get();

		}


		cout << contador1 << " " << contador2 << endl;


	}

	return 0;
}