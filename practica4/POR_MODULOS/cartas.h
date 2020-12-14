/* LUIS POZAS PALOMO 1ºF */
#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

const int CARTAS = 38;

typedef enum { AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER } tCarta;
typedef tCarta *tVCartas[CARTAS]; //VECTOR PARA EL MAZO

typedef struct {
	tVCartas cartas;
	int cont;
} tMazo;

void rellenarMazo(tMazo& mazo);
bool sacar(tMazo& mazo, tCarta& carta);
void insertar(tMazo& mazo, tCarta carta);
void crearMazoAleatorio(tMazo& mazo);
void liberarMazo(tMazo& mazo);