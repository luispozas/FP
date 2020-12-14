/* LUIS POZAS PALOMO 1ºF */
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "juego.h"
using namespace std;

const int TAM_INICIAL = 4;

typedef struct {
	string nombre;
	int puntos;
} tPuntos;

typedef struct {
	tPuntos *dinam;
	int tam;
	int capacidad;
} tPuntuaciones;

bool cargarPuntuaciones(tPuntuaciones& puntos);
void guardarPuntuaciones(const tPuntuaciones& puntos);
void mostrarPuntuaciones(const tPuntuaciones& puntos);
bool actualizarPuntuacion(tPuntuaciones& puntos, const string& nombre, int nuevos);
void redimensionar(tPuntuaciones & puntos);
void liberar(tPuntuaciones & puntos);
void ordenarPorNombre(tPuntuaciones& puntos);
void ordenarPorPuntos(tPuntuaciones& puntos);
bool compararNombres(string nombre1, string nombre2);
void copiarEstructura(tPuntuaciones& puntos, tPuntuaciones& puntosNombre);