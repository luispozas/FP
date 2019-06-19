#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int TAM = 8;
const int MAX_JUGADORES = 4;
const int incF[] = { -1, 0, 1, 0 };
const int incC[] = { 0, 1, 0, -1 };

typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { NORTE, ESTE, SUR, OESTE } tDir;

typedef struct {
	int numero;
	tDir direccion;
} tTortuga;

typedef struct {
	tEstadoCasilla tipo;
	tTortuga tortuga;
} tCasilla;

typedef struct {
	int x;
	int y;
} tCoordenada;

typedef tCasilla tTablero[TAM][TAM];

int resuelveCaso();
bool cargarTablero(tTablero tablero, int numjugadores);
void rellenarCasilla(tTablero tablero, tCoordenada coordenada, int& contadorjugador, char c);
bool desplazamientoTortuga (tTablero tablero, tCoordenada coordenada, tDir direcciontortuga2);



int main() {
#ifndef DOMJUDGE
	std::ifstream in("C:\\Users\\USUARIO\\Desktop\\Avanza.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE // PARA DEJAR TODO COMO ESTABA AL PRINCIPIO
	std::cin.rdbuf(cinbuf);
#endif
	system("pause");
	return 0;
}

int resuelveCaso() {
	bool encontradosDatos = false;
	string linea = "";
	int numJugadores = 0, tortugaAvanza = 0;
	tTablero tablero;

	cin >> numJugadores;

	while (numJugadores > 0) {
		cin >> tortugaAvanza;
		encontradosDatos = true;
		bool encontradaCoordenada = false;
		tCoordenada coordenada = { 0, 0 };
		tDir direcciontortuga2;

		if (cargarTablero(tablero, numJugadores)) {
			for (int i = 0; i < TAM && !encontradaCoordenada; i++) {
				for (int j = 0; j < TAM && !encontradaCoordenada; j++) {
					if (tablero[i][j].tortuga.numero == tortugaAvanza) {
						coordenada.x = i;
						coordenada.y = j;
						direcciontortuga2 = tablero[coordenada.x][coordenada.y].tortuga.direccion;
						encontradaCoordenada = true;
					}
				}
			}
			if (!desplazamientoTortuga(tablero, coordenada, direcciontortuga2)) {
				cout << "NO" << endl;
			}
			else if (desplazamientoTortuga(tablero, coordenada, direcciontortuga2)) {
				cout << "SI" << endl;
			}

			getline(cin, linea);
			while (cin && linea != "---") {
				getline(cin, linea);
			}
		}
		cin >> numJugadores;
	}
	return 0;
}

bool cargarTablero(tTablero tablero, int numjugadores) {
	int numjugfich;
	char c;
	string basura;
	tCoordenada coordenada;
	int contadorjugador = 0;
	bool cargado = false;

	cin >> numjugfich;
	getline(cin, basura);
	while (numjugadores != numjugfich) {
		for (int i = 0; i < TAM; i++) {
			getline(cin, basura);
		}
		cin >> numjugfich;
		getline(cin, basura);
	}

	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {
			coordenada = { i, j };
			cin.get(c);
			rellenarCasilla(tablero, coordenada, contadorjugador, c);
		}
		getline(cin, basura);
		cargado = true;
	}
	return cargado;
}

void rellenarCasilla(tTablero tablero, tCoordenada coordenada, int& contadorjugador, char c) {
	tCasilla casilla;
	tEstadoCasilla estado;
	tDir dir;

	switch (c) {
	case ' ': estado = VACIA; break;
	case 'C': estado = CAJA; break;
	case '#': estado = MURO; break;
	case '@': estado = HIELO; break;
	case '$': estado = JOYA; break;
	default: estado = TORTUGA; break;
	}
	casilla.tipo = estado;

	if (estado != TORTUGA) {
		casilla.tortuga.numero = 0;
	}
	else {
		contadorjugador++;
		casilla.tortuga.numero = contadorjugador;
		switch (c) {
		case 'D': dir = SUR; break;
		case 'R': dir = ESTE; break;
		case 'U': dir = NORTE; break;
		case 'L': dir = OESTE; break;
		}
		casilla.tortuga.direccion = dir;
	}
	tablero[coordenada.x][coordenada.y] = casilla;
}

bool correctasCoordenadas(tCoordenada coordenada) {
	bool correctasCoordenadas = false;
	if ((coordenada.x >= 0) && (coordenada.x <= TAM - 1) && (coordenada.y >= 0) && (coordenada.y <= TAM - 1)) {
		correctasCoordenadas = true;
	}
	return correctasCoordenadas;
}

bool desplazamientoTortuga (tTablero tablero, tCoordenada coordenada, tDir direcciontortuga2) {
	bool avanza = false;
	tCoordenada coordenadasiguiente = { coordenada.x + incF[direcciontortuga2], coordenada.y + incC[direcciontortuga2] }, coordenadasiguiente2 = { 0, 0 };

	if (correctasCoordenadas(coordenadasiguiente)) {
		if (tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == CAJA) {
			coordenadasiguiente2 = { coordenadasiguiente.x + incF[direcciontortuga2], coordenadasiguiente.y + incC[direcciontortuga2] };
			if ((tablero[coordenadasiguiente2.x][coordenadasiguiente2.y].tipo == VACIA) && (correctasCoordenadas(coordenadasiguiente2))) {
				avanza = true;
			}
		}
		else if ((tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == JOYA) || (tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == VACIA)) {
			avanza = true;
		}
	}
	return avanza;
}