#include "cartas.h"
#include "juego.h"
#include "puntuaciones.h"

using namespace std;

int main() {
	bool esFinDeLaPartida;
	string linea = "", nombreTablero;
	int op, p;
	char jugada;
	tJuego juego;
	tACartas arrayDeAcciones;
	tPuntuaciones puntos;

	cout << endl << "          || TORTUGAS ROBOTICAS || " << endl;
	op = menu();
	while (op != 0) {

		if (op == 1) {
			system("cls");
			cout << endl << " Introduce el nombre del fichero que contiene los tableros: ";
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
				cout << endl << "    LAS PUNTUACIONES SON: " << endl << endl;
				mostrarPuntuaciones(puntos);
			}
			op = menu();
		}
	}
	return 0;
}