#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX = 64;
const int TAM = 8;
const int MAX_JUGADORES = 4;
const int incF[] = { -1, 0, 1, 0 };
const int incC[] = { 0, 1, 0, -1 };

typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { NORTE, ESTE, SUR, OESTE } tDir;
typedef enum { AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER } tCarta;

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
typedef tCarta tVCartas[MAX];

int resuelveCaso();
bool cargarTablero(tTablero tablero, int numjugadores);
void rellenarCasilla(tTablero tablero, tCoordenada coordenada, int& contadorjugador, char c);
void dibujarTablero(const tTablero tablero);
bool correctasCoordenadas(tCoordenada coordenada);
void disparoLaser(tTablero& tablero, tCoordenada coordenada, tDir direcciontortuga1);
bool desplazamientoTortuga(tTablero tablero, tCoordenada coordenada, tDir direcciontortuga2);
bool avanzaTortuga(tTablero& tablero, tCoordenada coordenada, tCarta arrayDeAcciones, tDir& direcciontortuga3);
bool realizarMovimiento(tTablero& tablero, tCoordenada coordenada, tVCartas arrayDeAcciones, const int numeroDeAcciones, const int tortugaDesplazar);
tCarta string2enum(string acciones);


int main() {
#ifndef DOMJUDGE
	std::ifstream in("C:\\hlocal\\aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\\Mover.txt");
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
	bool joya = false;
	string linea = "";
	int numJugadores = 0, tortugaDesplazar = 0, numeroDeAcciones = 0;
	tTablero tablero;
	tVCartas arrayDeAcciones;
	string acciones;

	cin >> numJugadores;

	while (numJugadores > 0) {
		cin >> tortugaDesplazar;
		cin >> numeroDeAcciones;
		encontradosDatos = true;

		for (int i = 0; i < numeroDeAcciones; i++) {
			cin >> acciones;
			arrayDeAcciones[i] = string2enum(acciones);
		}

		tCoordenada coordenada = { 0, 0 };

		if (cargarTablero(tablero, numJugadores)) {

			if (realizarMovimiento(tablero, coordenada, arrayDeAcciones, numeroDeAcciones, tortugaDesplazar)){
				cout << "JOYA";
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
				cout << endl;
			}
			else {
				dibujarTablero(tablero);
				cout << endl;
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

bool correctasCoordenadas(tCoordenada coordenada) {
	bool correctasCoordenadas = false;

	if ((coordenada.x >= 0) && (coordenada.x <= TAM - 1) && (coordenada.y >= 0) && (coordenada.y <= TAM - 1)) {
		correctasCoordenadas = true;
	}
	return correctasCoordenadas;
}

void disparoLaser(tTablero& tablero, tCoordenada coordenada, tDir direcciontortuga1) {

	bool encontradoHielo = false;
	bool encontradoOtroElemento = false;
	tCoordenada coordenadasiguiente;
	coordenadasiguiente = { coordenada.x + incF[direcciontortuga1], coordenada.y + incC[direcciontortuga1] };

	while ((correctasCoordenadas(coordenadasiguiente)) && (!encontradoHielo) && (!encontradoOtroElemento)) {
		if (tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == HIELO) {
			tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo = VACIA;
			encontradoHielo = true;
		}
		else if (tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == VACIA) {
			coordenadasiguiente.x = coordenadasiguiente.x + incF[direcciontortuga1];
			coordenadasiguiente.y = coordenadasiguiente.y + incC[direcciontortuga1];
		}
		else { encontradoOtroElemento = true; }
	}
}

bool desplazamientoTortuga(tTablero tablero, tCoordenada coordenada, tDir direcciontortuga2) {
	bool desplazamientoTortuga = false;
	tCoordenada coordenadasiguiente = { coordenada.x + incF[direcciontortuga2], coordenada.y + incC[direcciontortuga2] }, coordenadasiguiente2 = { 0, 0 };

	if (correctasCoordenadas(coordenadasiguiente)) {
		if (tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == CAJA) {
			coordenadasiguiente2 = { coordenadasiguiente.x + incF[direcciontortuga2], coordenadasiguiente.y + incC[direcciontortuga2] };
			if ((tablero[coordenadasiguiente2.x][coordenadasiguiente2.y].tipo == VACIA) && (correctasCoordenadas(coordenadasiguiente2))) {
				desplazamientoTortuga = true;
			}
		}
		else if ((tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == JOYA) || (tablero[coordenadasiguiente.x][coordenadasiguiente.y].tipo == VACIA)) {
			desplazamientoTortuga = true;
		}
	}
	return desplazamientoTortuga;
}

bool avanzaTortuga(tTablero& tablero, tCoordenada coordenada, tCarta arrayDeAcciones, tDir& direcciontortuga3) {
	tCoordenada siguiente = { coordenada.x + incF[direcciontortuga3], coordenada.y + incC[direcciontortuga3] };
	tCoordenada siguiente2 = { siguiente.x + incF[direcciontortuga3], siguiente.y + incC[direcciontortuga3] };
	bool cierto = false;

	if (arrayDeAcciones == AVANZAR) {
		if ((tablero[siguiente.x][siguiente.y].tipo == JOYA) || (tablero[siguiente.x][siguiente.y].tipo == VACIA)) {

			if (tablero[siguiente.x][siguiente.y].tipo == JOYA) { cierto = true; }

			tablero[siguiente.x][siguiente.y].tipo = TORTUGA;
			tablero[siguiente.x][siguiente.y].tortuga.numero = tablero[coordenada.x][coordenada.y].tortuga.numero;
			tablero[siguiente.x][siguiente.y].tortuga.direccion = tablero[coordenada.x][coordenada.y].tortuga.direccion;
			tablero[coordenada.x][coordenada.y].tortuga.numero = 0;
			tablero[coordenada.x][coordenada.y].tipo = VACIA;
		}
		else if (tablero[siguiente.x][siguiente.y].tipo == CAJA) {

			tablero[siguiente.x][siguiente.y].tipo = TORTUGA;
			tablero[siguiente.x][siguiente.y].tortuga.numero = tablero[coordenada.x][coordenada.y].tortuga.numero;
			tablero[siguiente.x][siguiente.y].tortuga.direccion = tablero[coordenada.x][coordenada.y].tortuga.direccion;
			tablero[siguiente2.x][siguiente2.y].tipo = CAJA;
			tablero[coordenada.x][coordenada.y].tortuga.numero = 0;
			tablero[coordenada.x][coordenada.y].tipo = VACIA;
		}
	}
	else if (arrayDeAcciones == GIROIZQUIERDA) {
		switch (tablero[coordenada.x][coordenada.y].tortuga.direccion) {
		case NORTE: tablero[coordenada.x][coordenada.y].tortuga.direccion = OESTE; break;
		case ESTE: tablero[coordenada.x][coordenada.y].tortuga.direccion = NORTE; break;
		case SUR: tablero[coordenada.x][coordenada.y].tortuga.direccion = ESTE; break;
		case OESTE: tablero[coordenada.x][coordenada.y].tortuga.direccion = SUR; break;
		}
	}
	else if (arrayDeAcciones == GIRODERECHA) {
		switch (tablero[coordenada.x][coordenada.y].tortuga.direccion) {
		case NORTE: tablero[coordenada.x][coordenada.y].tortuga.direccion = ESTE; break;
		case ESTE: tablero[coordenada.x][coordenada.y].tortuga.direccion = SUR; break;
		case SUR: tablero[coordenada.x][coordenada.y].tortuga.direccion = OESTE; break;
		case OESTE: tablero[coordenada.x][coordenada.y].tortuga.direccion = NORTE; break;
		}
	}
	else if (arrayDeAcciones == LASER) {
		disparoLaser(tablero, coordenada, direcciontortuga3);
	}
	return cierto;
}

bool realizarMovimiento(tTablero& tablero, tCoordenada coordenada, tVCartas arrayDeAcciones, const int numeroDeAcciones, const int tortugaDesplazar) {
	bool encontradaCoordenada = false;
	bool encontradaJoya = false;
	tDir direcciontortuga;
	int k = 0;

	while ((k < numeroDeAcciones) && (!encontradaJoya)) { //SI TIENE UN MAZO DE CARTAS Y LA PRIMERA NO SE CUMPLE, LAS QUE VIENEN DESPUES SE TIENEN QUE HCAER O NO¿?
		for (int i = 0; i < TAM && !encontradaCoordenada; i++) {
			for (int j = 0; j < TAM && !encontradaCoordenada; j++) {
				if (tablero[i][j].tortuga.numero == tortugaDesplazar) {
					coordenada.x = i;
					coordenada.y = j;
					direcciontortuga = tablero[coordenada.x][coordenada.y].tortuga.direccion;
					encontradaCoordenada = true;
				}
			}
		}

		if (arrayDeAcciones[k] == AVANZAR) {
			if (desplazamientoTortuga(tablero, coordenada, direcciontortuga)) {
				encontradaJoya = avanzaTortuga(tablero, coordenada, arrayDeAcciones[k], tablero[coordenada.x][coordenada.y].tortuga.direccion);
			}
		}
		else {
			encontradaJoya = avanzaTortuga(tablero, coordenada, arrayDeAcciones[k], tablero[coordenada.x][coordenada.y].tortuga.direccion);
		}
		encontradaCoordenada = false;
		k++;
	}
	return encontradaJoya;
}

tCarta string2enum(string acciones) {
	tCarta enumerado;

	if (acciones == "AVANZAR") {
		enumerado = AVANZAR;
	}
	if (acciones == "GIROIZQUIERDA") {
		enumerado = GIROIZQUIERDA;
	}
	if (acciones == "GIRODERECHA") {
		enumerado = GIRODERECHA;
	}
	if (acciones == "LASER") {
		enumerado = LASER;
	}
	return enumerado;
}