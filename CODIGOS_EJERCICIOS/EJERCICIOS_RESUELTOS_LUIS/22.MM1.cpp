/*LUIS POZAS PALOMO y PABLO ALVAREZ GARCIA*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

const int TAM_CODIGO = 4;

typedef enum { ROJO, AZUL, VERDE, AMARILLO, MARRON, BLANCO } tColor;
typedef tColor tCodigo[TAM_CODIGO];
typedef bool tArray[TAM_CODIGO];

void compararCodigos(const tCodigo secreto, const tCodigo hipotesis, int& colocados, int& descolocados);
tColor char2colorhipotesis(char codigohumano);
tColor char2colorsecreto(char codigosecreto);

int main() {
	int colocados, descolocados;
	int j = 0;
	tCodigo secreto, hipotesis;
	string codigohumano, codigosecreto;

	cin >> codigohumano;
	cin >> codigosecreto;
	while ((codigohumano[0] != 'X') && (codigosecreto[0] != 'X')) {
		for (int j = 0; j < TAM_CODIGO; j++) {
			codigohumano[j] = toupper(codigohumano[j]);
			codigosecreto[j] = toupper(codigosecreto[j]);
		}
		for (int k = 0; k < TAM_CODIGO; k++) {
			hipotesis[k] = char2colorhipotesis(codigohumano[k]);
			secreto[k] = char2colorsecreto(codigosecreto[k]);
		}
		colocados = 0;
		descolocados = 0;
		compararCodigos(secreto, hipotesis, colocados, descolocados);
		cin >> codigohumano;
		cin >> codigosecreto;
	}

	system("pause");
	return 0;
}

void compararCodigos(const tCodigo secreto, const tCodigo hipotesis, int& colocados, int& descolocados) {
	int k, j = 0;
	tArray arraybool, comparadovertical;
	bool localizado = false;

	for (int i = 0; i < TAM_CODIGO; i++) {
		arraybool[i] = false;
		comparadovertical[i] = false;
	}

	for (int i = 0; i < TAM_CODIGO; i++) {
		if (hipotesis[i] == secreto[i]) {
			colocados++;
			arraybool[i] = true;
			comparadovertical[i] = true;
		}
	}
	while (j < TAM_CODIGO) {
		k = 0;
		localizado = false;
		if (!comparadovertical[j]) {
			while ((!localizado) && (k < TAM_CODIGO)) {
				if ((hipotesis[j] == secreto[k]) && (!arraybool[k])) {
					arraybool[k] = true;
					descolocados++;
					localizado = true;
				}
				k++;
			}
		}
		j++;
	}
	cout << colocados << " " << descolocados << endl;
}

tColor char2colorhipotesis(char codigohumano) {
	tColor color1;
	switch (codigohumano) {
	case 'R': color1 = ROJO; break;
	case 'Z': color1 = AZUL; break;
	case 'V': color1 = VERDE; break;
	case 'A': color1 = AMARILLO; break;
	case 'M': color1 = MARRON; break;
	case 'B': color1 = BLANCO; break;
	}
	return color1;
}

tColor char2colorsecreto(char codigosecreto) {
	tColor color2;
	switch (codigosecreto) {
	case 'R': color2 = ROJO; break;
	case 'Z': color2 = AZUL; break;
	case 'V': color2 = VERDE; break;
	case 'A': color2 = AMARILLO; break;
	case 'M': color2 = MARRON; break;
	case 'B': color2 = BLANCO; break;
	}
	return color2;
}