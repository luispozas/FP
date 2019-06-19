/* LUIS POZAS PALOMO */
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int TAMF = 6;
const int TAMC = 7;
const int inc[] = { -1, 1 };

typedef enum { VACIA, ROJA, AMARILLA } tFicha;
typedef tFicha tTablero[TAMF][TAMC];

typedef struct {
	int x;
	int y;
}tCoordenada;

bool comprobarDiagonal(const tTablero tablero, const tCoordenada coordenada, tFicha ficha);
bool comprobarVertical(const tTablero tablero, const tCoordenada coordenada, tFicha ficha);
bool comprobarHorizontal(const tTablero tablero, const tCoordenada coordenada, tFicha ficha);
bool CorrectasCoordenadas(int f, int c);
bool colocarFicha(tTablero& tablero, tFicha ficha, int posicion);
void inicializarTablero(tTablero& tablero);

int main() {
	int num1, aux;
	tTablero tablero;
	tFicha ficha;

	while (cin >> num1 && num1 != 0) {
		bool encontrado = false;
		bool ganaA = false, ganaB = false;
		inicializarTablero(tablero);
		for (int i = 0; i < num1; i++) {
			cin >> aux;
			if (i % 2 == 0) {
				ficha = AMARILLA;
				if (colocarFicha(tablero, ficha, aux) && !encontrado) {
					ganaA = true;
					encontrado = true;
				}
			}
			else if (i % 2 != 0) {
				ficha = ROJA;
				if (colocarFicha(tablero, ficha, aux) && !encontrado) {
					ganaB = true;
					encontrado = true;
				}
			}
		}
		if (ganaA) { cout << "Gana A" << endl; }
		else if (ganaB) { cout << "Gana B" << endl; }
		else { cout << "Empate" << endl; }
	}
	return 0;
}

void inicializarTablero(tTablero& tablero) {
	for (int i = 0; i < TAMF; i++) {
		for (int j = 0; j < TAMC; j++) {
			tablero[i][j] = VACIA;
		}
	}
}

bool colocarFicha(tTablero& tablero, tFicha ficha, int posicion) {
	bool colocarFicha = false;
	bool ganador = false;
	bool noInsertar = false;
	tCoordenada coordenada;
	int i = 0;

	while ((i < TAMF - 1) && (!colocarFicha) && (!noInsertar)) {
		if (tablero[i][posicion] == VACIA) {
			if (tablero[5][posicion] == VACIA) {
				tablero[5][posicion] = ficha;
				coordenada.x = 5;
				coordenada.y = posicion;
				colocarFicha = true;

				if (comprobarHorizontal(tablero, coordenada, ficha) || comprobarVertical(tablero, coordenada, ficha) || comprobarDiagonal(tablero, coordenada, ficha)) {
					ganador = true;
				}
			}
			else if (tablero[i + 1][posicion] != VACIA) {
				tablero[i][posicion] = ficha;
				coordenada.x = i;
				coordenada.y = posicion;
				colocarFicha = true;

				if (comprobarHorizontal(tablero, coordenada, ficha) || comprobarVertical(tablero, coordenada, ficha) || comprobarDiagonal(tablero, coordenada, ficha)) {
					ganador = true;
				}
			}
			else { i++; }
		}
		else { noInsertar = true; }
	}
	return ganador;
}

bool CorrectasCoordenadas(int f, int c) {
	bool ok = false;

	if (f <= 5 && f >= 0 && c <= 6 && c >= 0) {
		ok = true;
	}
	return ok;
}

bool comprobarHorizontal(const tTablero tablero, const tCoordenada coordenada, tFicha ficha) {
	int contadorH = 1;
	bool ganado = false;
	tCoordenada nuevacoordenada;

	nuevacoordenada.y = coordenada.y;

	while (tablero[coordenada.x][nuevacoordenada.y + inc[0]] == ficha && CorrectasCoordenadas(coordenada.x, nuevacoordenada.y + inc[0])) {
		contadorH++;
		nuevacoordenada.y = nuevacoordenada.y + inc[0];
	}

	nuevacoordenada.y = coordenada.y;

	while (tablero[coordenada.x][nuevacoordenada.y + inc[1]] == ficha && CorrectasCoordenadas(coordenada.x, nuevacoordenada.y + inc[1])) {
		contadorH++;
		nuevacoordenada.y = nuevacoordenada.y + inc[1];
	}

	if (contadorH >= 4) {
		ganado = true;
	}
	return ganado;
}

bool comprobarVertical(const tTablero tablero, const tCoordenada coordenada, tFicha ficha) {
	int contadorV = 1;
	bool ganado = false;
	tCoordenada nuevacoordenada;

	nuevacoordenada.x = coordenada.x;

	while (tablero[nuevacoordenada.x + inc[0]][coordenada.y] == ficha && CorrectasCoordenadas(nuevacoordenada.x + inc[0], coordenada.y)) {
		contadorV++;
		nuevacoordenada.x = nuevacoordenada.x + inc[0];
	}

	nuevacoordenada.x = coordenada.x;

	while (tablero[nuevacoordenada.x + inc[1]][coordenada.y] == ficha && CorrectasCoordenadas(nuevacoordenada.x + inc[1], coordenada.y)) {
		contadorV++;
		nuevacoordenada.x = nuevacoordenada.x + inc[1];
	}

	if (contadorV >= 4) {
		ganado = true;
	}
	return ganado;
}

bool comprobarDiagonal(const tTablero tablero, const tCoordenada coordenada, tFicha ficha) {
	int contadorD = 1;
	int contadorD2 = 1;
	bool ganado = false;
	tCoordenada nuevacoordenada;

	//COMPRUEBO PRIMERO POR LA DIAGONAL QUE VA DE IZQUIERDA A DERECHA

	nuevacoordenada.x = coordenada.x;
	nuevacoordenada.y = coordenada.y;

	while (tablero[nuevacoordenada.x + inc[0]][nuevacoordenada.y + inc[0]] == ficha && CorrectasCoordenadas(nuevacoordenada.x + inc[0], nuevacoordenada.y + inc[0])) {
		contadorD++;
		nuevacoordenada.x = nuevacoordenada.x + inc[0];
		nuevacoordenada.y = nuevacoordenada.y + inc[0];
	}

	nuevacoordenada.x = coordenada.x;
	nuevacoordenada.y = coordenada.y;

	while (tablero[nuevacoordenada.x + inc[1]][nuevacoordenada.y + inc[1]] == ficha && CorrectasCoordenadas(nuevacoordenada.x + inc[1], nuevacoordenada.y + inc[1])) {
		contadorD++;
		nuevacoordenada.x = nuevacoordenada.x + inc[1];
		nuevacoordenada.y = nuevacoordenada.y + inc[1];
	}

	if (contadorD >= 4) {
		ganado = true;
	}
	else {

		//COMPRUEBO DESPUES POR LA DIAGONAL QUE VA DE DERECHA A IZQUIERDA

		nuevacoordenada.x = coordenada.x;
		nuevacoordenada.y = coordenada.y;

		while (tablero[nuevacoordenada.x + inc[0]][nuevacoordenada.y + inc[1]] == ficha && CorrectasCoordenadas(nuevacoordenada.x + inc[0], nuevacoordenada.y + inc[1])) {
			contadorD2++;
			nuevacoordenada.x = nuevacoordenada.x + inc[0];
			nuevacoordenada.y = nuevacoordenada.y + inc[1];
		}

		nuevacoordenada.x = coordenada.x;
		nuevacoordenada.y = coordenada.y;

		while (tablero[nuevacoordenada.x + inc[1]][nuevacoordenada.y + inc[0]] == ficha && CorrectasCoordenadas(nuevacoordenada.x + inc[1], nuevacoordenada.y + inc[0])) {
			contadorD2++;
			nuevacoordenada.x = nuevacoordenada.x + inc[1];
			nuevacoordenada.y = nuevacoordenada.y + inc[0];
		}

		if (contadorD2 >= 4) {
			ganado = true;
		}
	}
	return ganado;
}