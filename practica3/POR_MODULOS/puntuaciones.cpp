#include "puntuaciones.h"

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
		cout << "      " << puntos[i].nombre << " " << puntos[i].puntos << endl;
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