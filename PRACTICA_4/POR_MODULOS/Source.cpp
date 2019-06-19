/* LUIS POZAS PALOMO 1ºF */
#include "cartas.h"
#include "juego.h"
#include "puntuaciones.h"
#include "checkML.h"

using namespace std;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	bool esFinDeLaPartida;
	string linea = "", nombreTablero;
	int op, op2, p;
	char jugada;
	tJuego juego;
	tACartas arrayDeAcciones;
	tPuntuaciones puntos, puntosNombre;
	puntos.capacidad = TAM_INICIAL;
	puntos.dinam = new tPuntos[TAM_INICIAL];

	cout << endl << "         || TORTUGAS ROBOTICAS || " << endl;
	op = menu();
	if (cargarPuntuaciones(puntos)) {
		ordenarPorPuntos(puntos);
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
						}
						cambiarTurno(juego);
						system("cls");
					}
					for (int j = 0; j < juego.numeroJugadores; j++) {
						liberarMazo(juego.registroJugadores[j].mazo);
					}

				}
				op = menu();
			}
			else if (op == 2) {
				system("cls");
				op2 = menu2();
				system("cls");

				if (op2 == 1) {
					cout << endl << "    LAS PUNTUACIONES POR ORDEN DE PUNTOS SON: " << endl << endl;
					mostrarPuntuaciones(puntos);
					cout << endl << endl;
					system("pause");
					system("cls");
				}
				else if (op2 == 2) {
					cout << endl << "    LAS PUNTUACIONES POR ORDEN ALFABETICO SON: " << endl << endl;
					copiarEstructura(puntos, puntosNombre);
					ordenarPorNombre(puntosNombre);
					mostrarPuntuaciones(puntosNombre);
					liberar(puntosNombre);
					cout << endl << endl;
					system("pause");
					system("cls");
				}
				op = menu();
			}
		}
	}
	guardarPuntuaciones(puntos);
	liberar(puntos);
	return 0;
}