/*
POZAS PALOMO
LUIS
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAX = 10;
typedef int tArray[MAX];



int main(){
	srand(time(NULL));
	int suma = 0, j=0;
	float media = 0;
	tArray mivector;

	// MUESTRO LOS 10 NUMEROS Y APROBECHO A REALIZAR LA SUMA
	cout << "Los diez numeros son: |";
	for (int i = 0; i < 10; i++){
		mivector[i] = rand() % 10;
		suma = suma + mivector[i];

		cout << mivector[i] << "|";
	}

	// REALIZO LA MEDIA Y LA MUESTRO
	media = suma / 10.0;
	cout << endl << "La media es: " << media << endl;

	// MUESTRO LA SUMA
	cout << "La suma es: " << suma << endl;

	// REALIZO LA BUSQUEDA DE LOS VALORES MAYORES QUE LA MEDIA
	cout << "Los numeros mayores de " << media << ": |";
	while (j < 10){
		if (mivector[j] > media){
			cout << mivector[j]<< "|";
		}
		j++;
	}
	cout << endl;

	system("pause");
	return 0;
}

