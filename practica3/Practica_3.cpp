/* LUIS POZAS PALOMO */
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>

using namespace std;

const int TAM = 8;
const int MAX_JUGADORES = 4;
const int CARTAS = 38;
const int incF[] = { -1, 0, 1, 0 };
const int incC[] = { 0, 1, 0, -1 };
const int PALETATORTUGAS[] = { 5, 13, 9, 10 };

typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { NORTE, ESTE, SUR, OESTE } tDir;
typedef enum { AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER } tCarta;
typedef enum { AVANZA, DERECHA, IZQUIERDA, PISTOLALASER, SALIR, NADA } tTecla;

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
typedef tCarta tVCartas[CARTAS]; // VECTOR PARA EL MAZO
typedef tCarta tACartas[CARTAS]; // ARRAY PARA LA SECUENCIA QUE DESEA REALIZAR

typedef struct {
	tVCartas cartas;
	int cont;
} tMazo;

typedef struct {
	int contA;
	int contI;
	int contD;
	int contL;
} tMano;

typedef struct {
	string nombre;
	tMazo mazo;
	tMano mano;
	tCoordenada coordenada;
} tJugador;

typedef tJugador tRegistro[MAX_JUGADORES];

typedef struct {
	int numeroJugadores;
	int turno;
	tRegistro registroJugadores;
	tTablero tablero;
} tJuego;

typedef struct {
	string nombre;
	int puntos;
} tPuntos;

typedef tPuntos tPuntuaciones[MAX_JUGADORES];

bool cargarTablero(tTablero tablero, int numjugadores, const string nombreTablero);
void rellenarCasilla(tTablero tablero, tCoordenada coordenada, int& contadorjugador, char c);
void dibujarTablero(const tTablero tablero);
bool correctasCoordenadas(tCoordenada coordenada);
void disparoLaser(tTablero& tablero, tCoordenada coordenada, tDir direcciontortuga1);
bool desplazamientoTortuga(tTablero tablero, tCoordenada coordenada, tDir direcciontortuga2);
bool avanzaTortuga(tTablero& tablero, tCoordenada coordenada, tCarta arrayDeAcciones, tDir& direcciontortuga3);
bool realizarMovimiento(tTablero& tablero, tCoordenada coordenada, tACartas arrayDeAcciones, const int numeroDeAcciones, const int tortugaDesplazar);
tTecla leerTecla();
int menu();
void rellenarMazo(tMazo& mazo);
bool sacar(tMazo& mazo, tCarta& carta);
void insertar(tMazo& mazo, tCarta carta);
void crearMazoAleatorio(tMazo& mazo);
void inicializarMano(tMano& mano);
bool accionRobar(tJuego& juego);
void cambiarTurno(tJuego& juego);
void incluirCarta(tMano &mano, tCarta carta);
void dibujarMarcador(tJuego& juego);
void secuenciaTeclas(tJuego& juego, tACartas& arrayDeAcciones, int& p);
void colorFondo(int color);
void mostrarPuntuaciones(const tPuntuaciones& puntos);
bool cargarPuntuaciones(tPuntuaciones& puntos);
void guardarPuntuaciones(const tPuntuaciones& puntos);
bool actualizarPuntuacion(tPuntuaciones& puntos, const string& nombre, int nuevos);
bool abrirTablero(const string nombreTablero);

int main() {
	bool esFinDeLaPartida;
	string linea = "", nombreTablero;
	int op, p;
	char jugada;
	tJuego juego;
	tACartas arrayDeAcciones;
	tPuntuaciones puntos;

	op = menu();
	while (op != 0) {

		if (op == 1) {
			system("cls");
			cout << " Introduce el nombre del fichero que contiene los tableros: ";
			cin >> nombreTablero;
			while (!abrirTablero(nombreTablero)) {
				cout << " Introduce un nombre valido: ";
				cin >> nombreTablero;
			}

			cout << endl << " Introduce el numero de jugadores: ";
			cin >> juego.numeroJugadores;
			while (juego.numeroJugadores > 4 || juego.numeroJugadores < 1) {
				cout << " Introduce un numero valido: ";
				cin >> juego.numeroJugadores;
			}
			cout << endl;
			for (int i = 0; i < juego.numeroJugadores; i++) {
				cout << " Introduce nombre del jugador: ";
				cin >> juego.registroJugadores[i].nombre;
				crearMazoAleatorio(juego.registroJugadores[i].mazo);
				inicializarMano(juego.registroJugadores[i].mano);
			}

			system("cls");

			if (cargarTablero(juego.tablero, juego.numeroJugadores, nombreTablero)) {
				if (cargarPuntuaciones(puntos)) {
					juego.turno = 1;
					esFinDeLaPartida = false;
					while (!esFinDeLaPartida) {
						dibujarTablero(juego.tablero);
						cout << endl << endl << "  JUGADORES: " << endl;
						dibujarMarcador(juego);
						cout << endl << endl;
						cout << " Robar carta (R) o para crear y ejecutar una secuencia (E)" << endl;
						cin >> jugada;
						jugada = toupper(jugada);
						if (jugada == 'R') {
							if (!accionRobar(juego)) {
								cout << " No puedes robar mas cartas de tu mazo" << endl;
							}
						}
						else if (jugada == 'E') {
							cout << " Con las flechas: ^ avanzar, > girar a la derecha, < girar a la izquierda y espacio para el laser:" << endl;

							p = 0;
							secuenciaTeclas(juego, arrayDeAcciones, p);

							esFinDeLaPartida = realizarMovimiento(juego.tablero, juego.registroJugadores[juego.turno - 1].coordenada, arrayDeAcciones, p, juego.turno);

							random_shuffle(arrayDeAcciones, arrayDeAcciones + p);
							for (int j = 0; j < p; j++) {
								insertar(juego.registroJugadores[juego.turno - 1].mazo, arrayDeAcciones[j]);
							}
						}

						if (esFinDeLaPartida) {
							actualizarPuntuacion(puntos, juego.registroJugadores[juego.turno - 1].nombre, juego.numeroJugadores);
							guardarPuntuaciones(puntos);
						}

						cambiarTurno(juego);
						system("cls");
					}
				}
			}
			op = menu();
		}
		else if (op == 2) {
			system("cls");
			if (cargarPuntuaciones(puntos)) {
				cout << " LAS PUNTUACIONES SON: " << endl;
				mostrarPuntuaciones(puntos);
			}
			op = menu();
		}
	}
	return 0;
}

void secuenciaTeclas(tJuego& juego, tACartas& arrayDeAcciones, int& p) {
	tTecla teclaPulsada;

	teclaPulsada = leerTecla();
	while (teclaPulsada != SALIR) {
		if ((teclaPulsada != NADA) && (p < CARTAS)) {
			if (teclaPulsada == AVANZA && juego.registroJugadores[juego.turno - 1].mano.contA > 0) {
				arrayDeAcciones[p] = AVANZAR;
				p++;
				cout << " ^ ";
				juego.registroJugadores[juego.turno - 1].mano.contA--;
			}
			else if (teclaPulsada == DERECHA && juego.registroJugadores[juego.turno - 1].mano.contD > 0) {
				arrayDeAcciones[p] = GIRODERECHA;
				p++;
				cout << " > ";
				juego.registroJugadores[juego.turno - 1].mano.contD--;
			}
			else if (teclaPulsada == IZQUIERDA && juego.registroJugadores[juego.turno - 1].mano.contI > 0) {
				arrayDeAcciones[p] = GIROIZQUIERDA;
				p++;
				cout << " < ";
				juego.registroJugadores[juego.turno - 1].mano.contI--;
			}
			else if (teclaPulsada == PISTOLALASER && juego.registroJugadores[juego.turno - 1].mano.contL > 0) {
				arrayDeAcciones[p] = LASER;
				p++;
				cout << " ~ ";
				juego.registroJugadores[juego.turno - 1].mano.contL--;
			}
		}
		teclaPulsada = leerTecla();
	}
}

void dibujarMarcador(tJuego& juego) {
	cout << endl;
	for (int i = 0; i < juego.numeroJugadores; i++) {
		if (juego.turno - 1 == i) { cout << ">"; }
		colorFondo(PALETATORTUGAS[i]); cout << setw(10) << juego.registroJugadores[i].nombre << ":"; colorFondo(0);
		cout << setw(2) << juego.registroJugadores[i].mano.contA;
		colorFondo(3); cout << " ^ "; colorFondo(0);
		cout << setw(2) << juego.registroJugadores[i].mano.contI;
		colorFondo(3); cout << " < "; colorFondo(0);
		cout << setw(2) << juego.registroJugadores[i].mano.contD;
		colorFondo(3); cout << " > "; colorFondo(0);
		cout << setw(2) << juego.registroJugadores[i].mano.contL;
		colorFondo(3); cout << " ~ "; colorFondo(0);
		cout << endl;
	}
}

bool cargarTablero(tTablero tablero, int numjugadores, const string nombreTablero) {
	int numjugfich;
	char c;
	string basura;
	tCoordenada coordenada;
	int contadorjugador = 0;
	bool cargado = false;

	ifstream archivo;
	archivo.open(nombreTablero);
	if (!archivo.is_open()) {
		cout << "ERROR AL ABRIR EL ARCHIVO DE LOS TABLEROS" << endl;
	}
	else {
		archivo >> numjugfich;
		getline(archivo, basura);
		while (numjugadores != numjugfich) {
			for (int i = 0; i < TAM; i++) {
				getline(archivo, basura);
			}
			archivo >> numjugfich;
			getline(archivo, basura);
		}

		for (int i = 0; i < TAM; i++) {
			for (int j = 0; j < TAM; j++) {
				coordenada = { i, j };
				archivo.get(c);
				rellenarCasilla(tablero, coordenada, contadorjugador, c);
			}
			getline(archivo, basura);
			cargado = true;
		}
	}
	archivo.close();
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
	cout << endl << endl;
	for (int i = 0; i < TAM; i++) {
		cout << "         ";
		for (int j = 0; j < TAM; j++) {

			switch (tablero[i][j].tipo) {
			case VACIA: colorFondo(1); cout << "  "; colorFondo(0); break;
			case MURO: colorFondo(7); cout << "||"; colorFondo(0); break;
			case HIELO: colorFondo(11); cout << "**"; colorFondo(0); break;
			case CAJA: colorFondo(4); cout << "[]"; colorFondo(0); break;
			case JOYA: colorFondo(12); cout << "00"; colorFondo(0); break;
			}

			if (tablero[i][j].tipo == TORTUGA) {
				switch (tablero[i][j].tortuga.direccion) {
				case NORTE: colorFondo(PALETATORTUGAS[tablero[i][j].tortuga.numero - 1]); cout << "^^"; colorFondo(0); break;
				case SUR: colorFondo(PALETATORTUGAS[tablero[i][j].tortuga.numero - 1]); cout << "vv"; colorFondo(0); break;
				case ESTE: colorFondo(PALETATORTUGAS[tablero[i][j].tortuga.numero - 1]); cout << ">>"; colorFondo(0); break;
				case OESTE: colorFondo(PALETATORTUGAS[tablero[i][j].tortuga.numero - 1]); cout << "<<"; colorFondo(0); break;
				}
			}
		}
		cout << endl;
	}
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
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

bool realizarMovimiento(tTablero& tablero, tCoordenada coordenada, tACartas arrayDeAcciones, const int numeroDeAcciones, const int tortugaDesplazar) {
	bool encontradaCoordenada = false;
	bool encontradaJoya = false;
	tDir direcciontortuga;
	int k = 0;

	while ((k < numeroDeAcciones) && (!encontradaJoya)) {
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

tTecla leerTecla() {
	tTecla teclaPulsada;
	int tecla;
	cin.sync();
	tecla = _getch();

	if (tecla == 0xe0) {
		tecla = _getch();
		switch (tecla) {
		case 72: teclaPulsada = AVANZA; break;
		case 77: teclaPulsada = DERECHA; break;
		case 75: teclaPulsada = IZQUIERDA; break;
		default: teclaPulsada = NADA; break;
		}
	}
	else {
		switch (tecla) {
		case 32: teclaPulsada = PISTOLALASER; break;
		case 13: teclaPulsada = SALIR; break;
		default: teclaPulsada = NADA; break;
		}
	}
	return teclaPulsada;
}

int menu() {
	int op;

	cout << endl;
	cout << "  1 - Jugar." << endl;
	cout << "  2 - Mostrar puntuaciones." << endl;
	cout << "  0 - Salir." << endl;
	cout << endl;
	cout << "  Opcion elegida: ";
	cin >> op;
	cout << endl;
	while ((op > 2) || (op < 0)) {
		cout << "  Introduzca una opcion valida: ";
		cin >> op;
	}

	return op;
}

void rellenarMazo(tMazo& mazo) {
	for (int i = 0; i < 18; i++) {
		mazo.cartas[i] = AVANZAR;
	}
	for (int j = 18; j < 26; j++) {
		mazo.cartas[j] = GIRODERECHA;
	}
	for (int w = 26; w < 34; w++) {
		mazo.cartas[w] = GIROIZQUIERDA;
	}
	for (int k = 34; k < 38; k++) {
		mazo.cartas[k] = LASER;
	}
	mazo.cont = 38;
}

bool sacar(tMazo& mazo, tCarta& carta) {
	bool accionSacar = false;

	if (mazo.cont > 0) {
		switch (mazo.cartas[0]) {
		case AVANZAR: carta = AVANZAR; break;
		case GIRODERECHA: carta = GIRODERECHA; break;
		case GIROIZQUIERDA: carta = GIROIZQUIERDA; break;
		case LASER: carta = LASER; break;
		}

		mazo.cont = mazo.cont - 1;

		for (int i = 0; i < mazo.cont; i++) {
			mazo.cartas[i] = mazo.cartas[i + 1];
		}
		accionSacar = true;
	}
	return accionSacar;
}

void insertar(tMazo& mazo, tCarta carta) {
	mazo.cartas[mazo.cont] = carta;
	mazo.cont = mazo.cont + 1;
}

void crearMazoAleatorio(tMazo& mazo) {
	rellenarMazo(mazo);
	random_shuffle(mazo.cartas, mazo.cartas + 38);
}

void inicializarMano(tMano& mano) {
	mano.contA = 0;
	mano.contI = 0;
	mano.contD = 0;
	mano.contL = 0;
}

bool accionRobar(tJuego& juego) {
	bool accionRobar = false;
	tCarta carta;

	if (sacar(juego.registroJugadores[juego.turno - 1].mazo, carta)) {
		incluirCarta(juego.registroJugadores[juego.turno - 1].mano, carta);
		accionRobar = true;
	}
	return accionRobar;
}

void cambiarTurno(tJuego& juego) {
	if (juego.numeroJugadores == 2) {
		switch (juego.turno) {
		case 1: juego.turno = 2; break;
		case 2: juego.turno = 1; break;
		}
	}
	else if (juego.numeroJugadores == 3) {
		switch (juego.turno) {
		case 1: juego.turno = 2; break;
		case 2: juego.turno = 3; break;
		case 3: juego.turno = 1; break;
		}
	}
	else if (juego.numeroJugadores == 4) {
		switch (juego.turno) {
		case 1: juego.turno = 2; break;
		case 2: juego.turno = 3; break;
		case 3: juego.turno = 4; break;
		case 4: juego.turno = 1; break;
		}
	}
}

void incluirCarta(tMano &mano, tCarta carta) {
	switch (carta) {
	case AVANZAR: mano.contA = mano.contA + 1; break;
	case GIRODERECHA: mano.contD = mano.contD + 1; break;
	case GIROIZQUIERDA: mano.contI = mano.contI + 1; break;
	case LASER: mano.contL = mano.contL + 1; break;
	}
}

bool cargarPuntuaciones(tPuntuaciones& puntos) {
	bool encontradasPuntuaciones = false;

	ifstream archivo;
	archivo.open("puntuaciones.txt");
	if (!archivo.is_open()) {
		cout << "ERROR AL ABRIR EL ARCHIVO DE LOS PUNTUACIONES" << endl;
	}
	else {
		for (int i = 0; i < MAX_JUGADORES; i++) {
			archivo >> puntos[i].nombre;
			archivo >> puntos[i].puntos;
			encontradasPuntuaciones = true;
		}
	}
	archivo.close();
	return encontradasPuntuaciones;
}

void guardarPuntuaciones(const tPuntuaciones& puntos) {

	ofstream archivo;
	archivo.open("puntuaciones.txt");
	if (!archivo.is_open()) {
		cout << "ERROR AL ABRIR EL ARCHIVO DE LOS PUNTUACIONES" << endl;
	}
	else {
		for (int i = 0; i < MAX_JUGADORES; i++) {
			archivo << puntos[i].nombre << " ";
			archivo << puntos[i].puntos;
			archivo << endl;
		}
	}
	archivo.close();
}

void mostrarPuntuaciones(const tPuntuaciones& puntos) {
	for (int i = 0; i < MAX_JUGADORES; i++) {
		cout << "   " << puntos[i].nombre << " " << puntos[i].puntos << endl;
	}
}

bool actualizarPuntuacion(tPuntuaciones& puntos, const string& nombre, int nuevos) {
	bool jugadornuevo = false;
	int posicion;

	for (int i = 0; i < MAX_JUGADORES; i++) {
		if (nombre == puntos[i].nombre) {
			puntos[i].puntos = puntos[i].puntos + nuevos;
			jugadornuevo = true;
		}
	}
	if (!jugadornuevo) {
		int menorpuntuacion = puntos[0].puntos;
		for (int j = 0; j < MAX_JUGADORES; j++) {
			if (puntos[j].puntos <= menorpuntuacion) {
				menorpuntuacion = puntos[j].puntos;
				posicion = j;
			}
		}
		if (nuevos > menorpuntuacion) {
			puntos[posicion].nombre = nombre;
			puntos[posicion].puntos = nuevos;
			jugadornuevo = true;
		}
	}
	return jugadornuevo;
}

bool abrirTablero(const string nombreTablero){
	bool abrirTablero=false;
	ifstream archivo;
	archivo.open(nombreTablero);
	if (!archivo.is_open()) {
		abrirTablero = false;
	}
	else {
		abrirTablero = true;
	}
	archivo.close();
	return abrirTablero;
}