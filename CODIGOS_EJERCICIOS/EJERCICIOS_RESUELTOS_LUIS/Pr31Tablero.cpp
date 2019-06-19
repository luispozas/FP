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

bool cargarTablero(tTablero tablero, int numjugadores);
void rellenarCasilla(tTablero tablero, tCoordenada coordenada, int& contadorjugador, char c);
void dibujarTablero(const tTablero tablero);

int resuelveCaso() {
	bool encontradosDatos = false;
	bool encontradaCoordenada = false;
	string linea = "";
	int numJugadores = 0, tortugaConLaser = 0;
	tTablero tablero;

	cin >> numJugadores;

	while (numJugadores > 0) {
		encontradosDatos = true;

		if (cargarTablero(tablero, numJugadores)){
			dibujarTablero(tablero);
			cout << endl;

			getline(cin, linea);
			while (cin && linea != "---"){
				getline(cin, linea);
			}
		}
		cin >> numJugadores; //PARA PODER LEER ESTE DATO TENGO QUE ELIMINAR "---", 
	}
	return 0;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("C:\\hlocal\\aaaaaaaaaaaaaaaaaa\\Tablero.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

#ifndef DOMJUDGE // PARA DEJAR TODO COMO ESTABA AL PRINCIPIO
	std::cin.rdbuf(cinbuf);
#endif
	system("pause");
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

void dibujarTablero(const tTablero tablero) {
	for (int i = 0; i < TAM; i++) {
		for (int j = 0; j < TAM; j++) {

			switch (tablero[i][j].tipo) {
			case VACIA: cout << "  "; break;
			case MURO: cout << "||"; break;
			case HIELO: cout << "**"; break;
			case CAJA: cout << "[]"; break;
			case JOYA: cout << "00"; break;
			}

			if (tablero[i][j].tipo == TORTUGA) {
				switch (tablero[i][j].tortuga.direccion) {
				case NORTE: cout << "^^"; break;
				case SUR: cout << "vv"; break;
				case ESTE: cout << ">>"; break;
				case OESTE: cout << "<<"; break;
				}
			}
		}
		cout << endl;
	}
}