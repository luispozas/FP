/* LUIS POZAS PALOMO 1ºF */
#include "juego.h"
#include "checkML.h"

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
	cout << "    ___________________________________ " << endl;
	cout << "   |                                   |" << endl;
	cout << "   |               MENU                |" << endl;
	cout << "   |___________________________________|" << endl;
	cout << "   |                                   |" << endl;
	cout << "   |     1 - Jugar.                    |" << endl;
	cout << "   |     2 - Mostrar puntuaciones.     |" << endl;
	cout << "   |                                   |" << endl;
	cout << "   |     0 - Salir.                    |" << endl;
	cout << "   |___________________________________|" << endl;
	cout << endl;
	cout << "     Opcion elegida: ";
	cin >> op;
	cout << endl;
	while ((op > 2) || (op < 0)) {
		cout << "     Introduzca una opcion valida: ";
		cin >> op;
	}

	return op;
}

int menu2() {
	int op;
	cout << endl;
	cout << "    ___________________________________ " << endl;
	cout << "   |                                   |" << endl;
	cout << "   |              SUBMENU              |" << endl;
	cout << "   |___________________________________|" << endl;
	cout << "   |                                   |" << endl;
	cout << "   |     1 - Por puntuacion            |" << endl;
	cout << "   |     2 - Por nombre                |" << endl;
	cout << "   |___________________________________|" << endl;
	cout << endl;
	cout << "     Opcion elegida: ";
	cin >> op;
	cout << endl;
	while ((op > 2) || (op < 1)) {
		cout << "     Introduzca una opcion valida: ";
		cin >> op;
	}

	return op;
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

bool abrirTablero(const string nombreTablero) {
	bool abrirTablero = false;
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