#include "cartas.h"

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
