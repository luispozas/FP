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

void crearcodigohipotesis(tCodigo& hipotesis);
void mostrarcodigoaleatorio(tCodigo& secreto, bool admiteRepetidos);
void compararCodigos(const tCodigo secreto, const tCodigo hipotesis, int& colocados, int& descolocados, bool& acertado);
int menu();
void reglasdeljuego();
void codigoAleatorio(tCodigo& secreto, bool admiteRepetidos);
tColor numero_tColor(int numeroaleatorio);
char color2char(tColor color);
tColor char2color(char codigohumano);

int main() {
	srand(time(NULL));
	int opcionmenu, colocados, descolocados;
	int vueltas;
	bool admiteRepetidos = false, acertado;
	tCodigo secreto, hipotesis;

	reglasdeljuego();
	opcionmenu = menu();
	while (opcionmenu != 0) {
		if ((opcionmenu < 0) || (opcionmenu > 2)) {
			cout << "  ERROR, introduzca una opcion perteneciente al menu. " << endl;
			opcionmenu = menu();
		}

		if ((opcionmenu == 1) || (opcionmenu == 2)) {
			acertado = false;
			vueltas = 0;

			switch (opcionmenu) {
			case 1:	admiteRepetidos = false; break;
			case 2: admiteRepetidos = true; break;
			}

			mostrarcodigoaleatorio(secreto, admiteRepetidos);

			while ((vueltas < 15) && (!acertado)) {
				crearcodigohipotesis(hipotesis);
				colocados = 0;
				descolocados = 0;
				compararCodigos(secreto, hipotesis, colocados, descolocados, acertado);
				vueltas++;
			}
			cout << "  TE HA COSTADO " << vueltas << " INTENTO(S)" << endl;
			opcionmenu = menu();
		}
	}
	system("pause");
	return 0;
}

void crearcodigohipotesis(tCodigo& hipotesis) {
	string codigohumano;
	int j = 0;
	cout << "  Introduce el codigo (palabra de 4 letras con alguna de R, Z, V, A, M o B): ";
	cin >> codigohumano;
	while (j < TAM_CODIGO) {
		codigohumano[j] = toupper(codigohumano[j]);
		if ((codigohumano[j] != 'R') && (codigohumano[j] != 'Z') && (codigohumano[j] != 'V') && (codigohumano[j] != 'A') && (codigohumano[j] != 'M') && (codigohumano[j] != 'B')) {
			cout << "  ERROR AL INTRODUCIR EL CODIGO, INTENTELO DE NUEVO: ";
			cin >> codigohumano;
			j = 0;
		}
		else { j++; }
	}
	for (int k = 0; k < TAM_CODIGO; k++) {
		hipotesis[k] = char2color(codigohumano[k]);
	}
}

void mostrarcodigoaleatorio(tCodigo& secreto, bool admiteRepetidos) {
	cout << "  [INFO para depuracion] Codigo secreto: ";
	codigoAleatorio(secreto, admiteRepetidos);
	for (int i = 0; i < TAM_CODIGO; i++) {
		cout << color2char(secreto[i]);
	}
	cout << endl;
}

void compararCodigos(const tCodigo secreto, const tCodigo hipotesis, int& colocados, int& descolocados, bool& acertado) {
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
	cout << "  COLOCADOS: " << colocados << " ||  MAL COLOCADOS: " << descolocados << endl;
	if (colocados == TAM_CODIGO) {
		acertado = true;
		cout << endl << "  Enhorabuena! Lo encontraste!" << endl;
	}
}

int menu() {
	int op;

	cout << endl;
	cout << "  1 - Jugar con un codigo sin colores repetidos" << endl;
	cout << "  2 - Jugar con un codigo con colores repetidos" << endl;
	cout << "  0 - Salir" << endl;
	cout << endl;
	cout << "  Opcion elegida: ";
	cin >> op;
	cout << endl;

	return op;
}

void reglasdeljuego() {
	cout << endl << endl;
	cout << "  _______________________________________________________________________" << endl;
	cout << " |                                                                       |" << endl;
	cout << " |                             MASTERMIND                                |" << endl;
	cout << " |                                                                       |" << endl;
	cout << " |  Descubre el codigo secreto! En cada partida, pensare un codigo de    |" << endl;
	cout << " |   colores que tendras que adivinar. En cada intento que hagas te      |" << endl;
	cout << " |  dare pistas, diciendote cuantos colores de los que has dicho estan   |" << endl;
	cout << " |                  bien colocados, y cuantos no.                        |" << endl;
	cout << " |                                                                       |" << endl;
	cout << " |  Averigua el codigo secreto en el menor numero posible de intentos!   |" << endl;
	cout << " |_______________________________________________________________________|" << endl << endl;
}

void codigoAleatorio(tCodigo& secreto, bool admiteRepetidos) {
	int numeroaleatorio;
	bool encontrado = false;

	if (admiteRepetidos) {
		for (int i = 0; i < TAM_CODIGO; i++) {
			numeroaleatorio = rand() % 6;
			secreto[i] = numero_tColor(numeroaleatorio);
		}
	}
	else if (!admiteRepetidos) {
		int j = 0;
		int i = 1;
		numeroaleatorio = rand() % 6;
		secreto[0] = numero_tColor(numeroaleatorio);
		while (i < TAM_CODIGO) {
			numeroaleatorio = rand() % 6;
			secreto[i] = numero_tColor(numeroaleatorio);
			encontrado = false;
			j = 0;
			while ((j < i) && (!encontrado)) {
				if (secreto[j] == secreto[i]) {
					encontrado = true;
				}
				j++;
			}
			if (!encontrado)
				i++;
		}
	}
}

tColor numero_tColor(int numeroaleatorio) {
	tColor color;
	switch (numeroaleatorio) {
	case 0: color = ROJO; break;
	case 1: color = AZUL; break;
	case 2: color = VERDE; break;
	case 3: color = AMARILLO; break;
	case 4: color = MARRON; break;
	case 5: color = BLANCO; break;
	}
	return color;
}

char color2char(tColor color) {
	char caracter;
	switch (color) {
	case ROJO: caracter = 'R'; break;
	case AZUL: caracter = 'Z'; break;
	case VERDE: caracter = 'V'; break;
	case AMARILLO: caracter = 'A'; break;
	case MARRON: caracter = 'M'; break;
	case BLANCO: caracter = 'B'; break;
	}
	return caracter;
}

tColor char2color(char codigohumano) {
	tColor color;
	switch (codigohumano) {
	case 'R': color = ROJO; break;
	case 'Z': color = AZUL; break;
	case 'V': color = VERDE; break;
	case 'A': color = AMARILLO; break;
	case 'M': color = MARRON; break;
	case 'B': color = BLANCO; break;
	}
	return color;
}