#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "juego.h"

using namespace std;

typedef struct {
	string nombre;
	int puntos;
} tPuntos;

typedef tPuntos tPuntuaciones[MAX_JUGADORES];

bool cargarPuntuaciones(tPuntuaciones& puntos);
void guardarPuntuaciones(const tPuntuaciones& puntos);
void mostrarPuntuaciones(const tPuntuaciones& puntos);
bool actualizarPuntuacion(tPuntuaciones& puntos, const string& nombre, int nuevos);