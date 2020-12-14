/*LUIS POZAS PALOMO y PABLO ALVAREZ GARCIA*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

typedef enum { piedra, papel, tijera, lagarto, spock } tElemento;
typedef enum { empate, ganaM, ganaH } tResultado;

bool localizacionJugador(string apodo);
int menu();
bool mostrarReglas();
tElemento eleccionHumano();
string elementoAstring(tElemento elemento);
int generadornumeroaleatorio();
tElemento eleccionmaquina(int numeromaquina);
string escrituraeleccionmaquina(tElemento elementomaquina);
tResultado quiengana(tElemento elementomaquina, tElemento elementohumano);
string escrituraquiengana(tResultado ganador);


bool localizacionJugador(string apodo) {

	bool encontrado = false;
	string nombre;

	ifstream archivo;
	archivo.open("registro.txt");
	if (!archivo.is_open()) {
		cout << "ERROR AL ABRIR EL ARCHIVO DEL REGISTRO" << endl;
	}

	else {
		getline(archivo, nombre);
		while (nombre != "XXX" && !encontrado) {
			getline(archivo, nombre);
			if (nombre == apodo) {
				encontrado = true;
			}

		}
		if (nombre != apodo) {
			cout << "Jugador no registrado. Imposible jugar." << endl;
		}
	}
	archivo.close();
	return encontrado;
}

int menu() {

	int op;

	cout << endl;
	cout << "1 - Jugar una partida" << endl;
	cout << "2 - Ver instrucciones" << endl;
	cout << "0 - Salir" << endl;
	cout << "Opcion: ";
	cin >> op;
	cout << endl;

	return op;
}

bool mostrarReglas() {

	bool muestra = false;
	string reglas;

	ifstream archivo;
	archivo.open("reglas.txt");
	if (!archivo.is_open()) {
		cout << "ERROR AL ABRIR EL ARCHIVO DE LAS REGLAS" << endl;
	}

	else {
		getline(archivo, reglas);

		while (reglas != "XXX") {
			cout << reglas << endl;
			getline(archivo, reglas);
		}
		muestra = true;
	}

	archivo.close();
	return muestra;
}

tElemento eleccionHumano() {

	tElemento humano;
	int eleccionhumano;

	cout << "Elige un elemento (1- piedra, 2- papel, 3- tijera, 4- lagarto, 5- spock): ";
	cin >> eleccionhumano;

	while ((eleccionhumano > 5) || (eleccionhumano < 1)) {
		cout << "Se a producido un error en la eleccion del elemento, introduzca un valor " << endl;
		cout << "de estos elementos (1- piedra, 2- papel, 3- tijera, 4- lagarto, 5- spock): " << endl;
		cin >> eleccionhumano;
	}
	eleccionhumano = eleccionhumano - 1;
	humano = (tElemento)eleccionhumano;

	return humano;

}

string elementoAstring(tElemento elemento) {

	string escrituraelemento;

	switch (elemento) {
	case piedra: escrituraelemento = "Piedra"; break;
	case papel: escrituraelemento = "Papel"; break;
	case tijera: escrituraelemento = "Tijera"; break;
	case lagarto: escrituraelemento = "Lagarto"; break;
	case spock: escrituraelemento = "Spock"; break;
	}
	return escrituraelemento;
}

int generadornumeroaleatorio() {
	int eleccionmaquina;
	eleccionmaquina = rand() % 5;

	return eleccionmaquina;

}

tElemento eleccionmaquina(int numeromaquina) {

	tElemento maquina;
	maquina = (tElemento)numeromaquina;

	return maquina;
}

string escrituraeleccionmaquina (tElemento elementomaquina) {

	string escrituramaquina;

	switch (elementomaquina) {
	case 0: escrituramaquina = "Piedra"; break;
	case 1: escrituramaquina = "Papel"; break;
	case 2: escrituramaquina = "Tijera"; break;
	case 3: escrituramaquina = "Lagarto"; break;
	case 4: escrituramaquina = "Spock"; break;
	}
	return escrituramaquina;
}

tResultado quiengana(tElemento elementomaquina, tElemento elementohumano) {

	tResultado partida;

	if (elementomaquina == elementohumano) { partida = empate; }
	else if ((elementohumano == tijera) && ((elementomaquina == papel) || (elementomaquina == lagarto))) { partida = ganaH; }
	else if ((elementohumano == papel) && ((elementomaquina == piedra) || (elementomaquina == spock))) { partida = ganaH; }
	else if ((elementohumano == piedra) && ((elementomaquina == lagarto) || (elementomaquina == tijera))) { partida = ganaH; }
	else if ((elementohumano == lagarto) && ((elementomaquina == spock) || (elementomaquina == papel))) { partida = ganaH; }
	else if ((elementohumano == spock) && ((elementomaquina == tijera) || (elementomaquina == piedra))) { partida = ganaH; }
	else  partida = ganaM;
	return partida;
}

string escrituraquiengana(tResultado ganador) {

	string escriturapartida;

	switch (ganador) {
	case empate: escriturapartida = "Se ha producido un empate"; break;
	case ganaM: escriturapartida = "Has perdido"; break;
	case ganaH: escriturapartida = "Has ganado"; break;
	}
	return escriturapartida;
}

int main() {

	srand(time(NULL));
	tElemento elementohumano, elementomaquina;
	tResultado ganador;
	int partidasganadas = 0, partidasperdidas = 0, opcionmenu, empates = 0, total = 0, numeromaquina;
	string apodo, nombrejugador, nombremaquina, resultado;
	bool puedejugar, mostrado;

	cout << "Dame un apodo: ";
	cin >> apodo;
	puedejugar = localizacionJugador(apodo);

	if (puedejugar) {
		opcionmenu = menu();

		while (opcionmenu != 0) {
			if ((opcionmenu < 0) || (opcionmenu > 2)) {
				cout << "ERROR, introduzca una opcion perteneciente al menu. " << endl;
				opcionmenu = menu();
			}
			if (opcionmenu == 2) {
				mostrado = mostrarReglas();
				opcionmenu = menu();
			}

			if (opcionmenu == 1) {

				numeromaquina = generadornumeroaleatorio();
				elementomaquina = eleccionmaquina(numeromaquina);
				nombremaquina = escrituraeleccionmaquina(elementomaquina);

				elementohumano = eleccionHumano();
				nombrejugador = elementoAstring(elementohumano);

				ganador = quiengana(elementomaquina, elementohumano);

				switch (ganador) {
				case empate: empates++; break;
				case ganaH: partidasganadas++; break;
				case ganaM: partidasperdidas++; break;
				}

				resultado = escrituraquiengana(ganador);

				cout << "Eleccion computadora: ";
				cout << nombremaquina << endl;
				cout << "Tu eleccion: ";
				cout << nombrejugador << endl;
				cout << "-----------------------" << endl;
				cout << resultado << endl;
				cout << endl;
				total = empates + partidasganadas + partidasperdidas;
				opcionmenu = menu();
			}
		}

		if (opcionmenu == 0) {

			cout << "Ronda de " << total << " partida(s)" << endl;
			cout << "Partidas ganadas: " << partidasganadas << endl;
			cout << "Partidas empatadas: " << empates << endl;
			cout << "Partidas perdidas: " << partidasperdidas << endl;
		}
	}
	system("pause");
	return 0;
}