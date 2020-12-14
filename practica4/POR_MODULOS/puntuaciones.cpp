/* LUIS POZAS PALOMO 1ºF */
#include "puntuaciones.h"
#include "checkML.h"

bool cargarPuntuaciones(tPuntuaciones& puntos) {
	bool encontradasPuntuaciones = false;
	puntos.tam = 0;

	ifstream archivo;
	archivo.open("puntuaciones.txt");
	if (!archivo.is_open()) {
		cout << "ERROR AL ABRIR EL ARCHIVO DE LAS PUNTUACIONES" << endl;
	}
	else {
		tPuntos obj;
		while (archivo >> obj.nombre && archivo >> obj.puntos) {
			if (puntos.capacidad == puntos.tam) {
				redimensionar(puntos);
			}
			puntos.dinam[puntos.tam].nombre = obj.nombre;
			puntos.dinam[puntos.tam].puntos = obj.puntos;
			puntos.tam++;
		}
		encontradasPuntuaciones = true;
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
		for (int i = 0; i < puntos.tam; i++) {
			archivo << puntos.dinam[i].nombre << " ";
			archivo << puntos.dinam[i].puntos;
			archivo << endl;
		}
	}
	archivo.close();
}

void mostrarPuntuaciones(const tPuntuaciones& puntos) { 
	for (int i = 0; i < puntos.tam; i++) {
		cout << "      " << puntos.dinam[i].nombre << " " << puntos.dinam[i].puntos << endl;
	}
}

bool actualizarPuntuacion(tPuntuaciones& puntos, const string& nombre, int nuevos) {
	bool jugadornuevo = true;

	for (int i = 0; i < puntos.tam; i++) {
		if (nombre == puntos.dinam[i].nombre) {
			puntos.dinam[i].puntos = puntos.dinam[i].puntos + nuevos;
			jugadornuevo = false;
			ordenarPorPuntos(puntos);
		}
	}
	if (jugadornuevo) {
		if (puntos.capacidad == puntos.tam) {
			redimensionar(puntos);
		}
		puntos.dinam[puntos.tam].nombre = nombre;
		puntos.dinam[puntos.tam].puntos = nuevos;
		puntos.tam++;
		ordenarPorPuntos(puntos);
	}
	return jugadornuevo;
}

 void redimensionar(tPuntuaciones& puntos) {
	tPuntos *aux = nullptr;

	aux = new tPuntos[4 + puntos.capacidad];
	for (int i = 0; i < puntos.tam; i++)
	{
		aux[i] = puntos.dinam[i];
	}
	delete[] puntos.dinam;
	puntos.dinam = aux;
	puntos.capacidad += 4;
	aux = nullptr;
}

void liberar(tPuntuaciones& puntos) {
	delete[] puntos.dinam;
	puntos.dinam = nullptr;
	puntos.tam = 0;
}

void ordenarPorPuntos(tPuntuaciones& puntos) {
	//ORDENACION POR METODO DE LA BURBUJA:

	bool inter = true;
	int i = 0;
	while ((i < puntos.tam - 1) && inter) {
		inter = false;
		for (int j = puntos.tam - 1; j > i; j--) {
			if (puntos.dinam[j].puntos > puntos.dinam[j - 1].puntos) {
				tPuntos tmp;
				tmp = puntos.dinam[j];
				puntos.dinam[j] = puntos.dinam[j - 1];
				puntos.dinam[j - 1] = tmp;

				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}

bool compararNombres(string nombre1, string nombre2){
	//Si el mayor es "nombre2" devuelvo un "1", sino un "0".
	//(Comparo nombres por las MAYUSCULAS ya que sino aparecerian antes que las MINUSCULAS).
	bool compararNombres = false;
	int tam1 = nombre1.size(), tam2 = nombre2.size();

	for (int i = 0; i < tam1; i++) {
		nombre1[i] = tolower(nombre1[i]);
	}
	for (int j = 0; j < tam2; j++) {
		nombre2[j] = tolower(nombre2[j]);
	}
	if (nombre1 < nombre2) {
		compararNombres = true;
	}
	return compararNombres;
}

void copiarEstructura(tPuntuaciones& puntos, tPuntuaciones& puntosNombre){
	puntosNombre.tam = puntos.tam;
	puntosNombre.capacidad = puntos.capacidad;
	puntosNombre.dinam = new tPuntos[puntosNombre.capacidad];
	for (int i = 0; i < puntos.tam; i++) {
		puntosNombre.dinam[i] = puntos.dinam[i];
	}
}

void ordenarPorNombre(tPuntuaciones& puntosNombre) {
	//ORDENACION POR METODO DE LA BURBUJA:

	bool inter = true;
	int i = 0;
	while ((i < puntosNombre.tam - 1) && inter) {
		inter = false;
		for (int j = puntosNombre.tam - 1; j > i; j--) {
			if (compararNombres(puntosNombre.dinam[j].nombre, puntosNombre.dinam[j - 1].nombre)) {
				tPuntos tmp;
				tmp = puntosNombre.dinam[j];
				puntosNombre.dinam[j] = puntosNombre.dinam[j - 1];
				puntosNombre.dinam[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}