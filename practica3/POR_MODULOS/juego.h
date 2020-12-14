#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <Windows.h>
#include "cartas.h"

using namespace std;

const int TAM = 8;
const int MAX_JUGADORES = 4;
const int incF[] = { -1, 0, 1, 0 };
const int incC[] = { 0, 1, 0, -1 };
const int PALETATORTUGAS[] = { 5, 13, 9, 10 };

typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { NORTE, ESTE, SUR, OESTE } tDir;
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
typedef tCarta tACartas[CARTAS]; // ARRAY PARA LA SECUENCIA QUE DESEA REALIZAR

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
void inicializarMano(tMano& mano);
bool accionRobar(tJuego& juego);
void cambiarTurno(tJuego& juego);
void incluirCarta(tMano &mano, tCarta carta);
void dibujarMarcador(tJuego& juego);
void secuenciaTeclas(tJuego& juego, tACartas& arrayDeAcciones, int& p);
void colorFondo(int color);
bool abrirTablero(const string nombreTablero);