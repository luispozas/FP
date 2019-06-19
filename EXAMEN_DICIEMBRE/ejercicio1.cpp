/*
POZAS PALOMO
LUIS
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	int num;
	string palabra;
	bool a = false, e = false, i = false, o = false, u = false;

	ifstream archivo;
	archivo.open("datos.txt");
	if (archivo.is_open()){

		archivo >> num;
		archivo >> palabra;

		for (int j = 0; j < num; j++){
			for (int p = 0; p < palabra.size(); p++){

				if (palabra[p] == 'a'){
					a = true;
				}
				else if (palabra[p] == 'e'){
					e = true;
				}
				else if (palabra[p] == 'i'){
					i = true;
				}
				else if (palabra[p] == 'o'){
					o = true;
				}
				else if (palabra[p] == 'u'){
					u = true;
				}

				if ((a == true) && (e == true) && (i == true) && (o == true) && (u == true)){
					cout << "La palabra " << palabra << " contiene todas las vocales." << endl;
				}
			}
			archivo >> palabra;
			a = false, e = false, i = false, o = false, u = false;
		}
	}
	else {
		cout << "ERROR AL ABRIR EL ARCHIVO" << endl;
	}

	system("pause");
	return 0;
}