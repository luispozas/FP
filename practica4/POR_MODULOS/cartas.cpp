/* LUIS POZAS PALOMO 1ºF */
#include "cartas.h"
#include "checkML.h"

void rellenarMazo(tMazo& mazo) {
	for (int i = 0; i < 18; i++) {
		mazo.cartas[i] = new tCarta(AVANZAR);
	}
	for (int j = 18; j < 26; j++) {
		mazo.cartas[j] = new tCarta(GIRODERECHA);
	}
	for (int w = 26; w < 34; w++) {
		mazo.cartas[w] = new tCarta(GIROIZQUIERDA);
	}
	for (int k = 34; k < 38; k++) {
		mazo.cartas[k] = new tCarta(LASER);
	}
	mazo.cont = 38;
}

bool sacar(tMazo& mazo, tCarta& carta) {
	bool accionSacar = false;

	if (mazo.cont > 0) {
		carta = *mazo.cartas[0];
		tCarta *aux = mazo.cartas[0];
		mazo.cont = mazo.cont - 1;

		for (int i = 0; i < mazo.cont; i++) {
			mazo.cartas[i] = mazo.cartas[i + 1];
		}
		mazo.cartas[mazo.cont] = aux;
		accionSacar = true;
	}
	return accionSacar;
}

void insertar(tMazo& mazo, tCarta carta) {
	*mazo.cartas[mazo.cont] = carta;
	mazo.cont = mazo.cont + 1;
}

void crearMazoAleatorio(tMazo& mazo) {
	rellenarMazo(mazo);
	random_shuffle(mazo.cartas, mazo.cartas + 38);
}

void liberarMazo(tMazo& mazo) { // ME DA ERROR
	for (int i = 0; i < CARTAS; i++) {
		delete mazo.cartas[i];
	}
	mazo.cont = 0;
}