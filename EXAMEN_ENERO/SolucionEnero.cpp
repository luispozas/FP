/*
Luis Pozas Palomo
Solucion al examen de enero
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NumPartidos = 5, NumCirc = 3;

typedef struct{
	string nombrePartido;
	int ideolog;
	int polTerritorial;
}tPartido;

typedef struct{
	string nombreCirc;
	int votos[NumPartidos];
}tCirc;

// Prototipos

bool cargar(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]);
void mostrarVotosPartido(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]);
void mostrarICD(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]);
void buscarIndGan(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]);

// Función principal
int main(){
	// Declaraciones de los arrays
	tPartido arrayPartidos[NumPartidos];
	tCirc arrayCirc[NumCirc];
	
	// Carga
	if (cargar(arrayPartidos, arrayCirc)){
		mostrarVotosPartido(arrayPartidos, arrayCirc);
		mostrarICD(arrayPartidos, arrayCirc);
		buscarIndGan(arrayPartidos, arrayCirc);
	}
	system("pause");
	return 0;
}

// Búsqueda con while
void buscarIndGan(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]){
	bool encontrado = false;
	int i = 0; 
		while(i < NumCirc && ! encontrado){
		int votosInd = 0, votosNoInd = 0;
		for (int j = 0; j < NumPartidos; j++){
			if (arrayPartidos[j].polTerritorial == 0 || arrayPartidos[j].polTerritorial == 1){
				votosNoInd += arrayCirc[i].votos[j];
			}
			else{
				votosInd += arrayCirc[i].votos[j];
			}
		}
		if (votosInd > votosNoInd){
			encontrado = true;
			cout << "Existe alguna circunscipción independentista, por ejemplo " << arrayCirc[i].nombreCirc << endl;
		}
		i++;
	}
}

// Recorrido
void mostrarICD(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]){
	int votosI = 0, votosC = 0, votosD = 0;
	for (int i = 0; i < NumPartidos; i++){
		if (arrayPartidos[i].ideolog == 0){
			for (int j = 0; j < NumCirc; j++){
				votosI += arrayCirc[j].votos[i];
			}
		}
		if (arrayPartidos[i].ideolog == 1){
			for (int j = 0; j < NumCirc; j++){
				votosC += arrayCirc[j].votos[i];
			}
		}
		if (arrayPartidos[i].ideolog == 2){
			for (int j = 0; j < NumCirc; j++){
				votosD += arrayCirc[j].votos[i];
			}
		}
	}
	cout << "Votos totales de izquierda: " << votosI << endl;
	cout << "Votos totales de izquierda o centro: " << votosI + votosC << endl;
	cout << "Votos totales de derecha: " << votosD << endl;
	cout << "Votos totales de derecha o centro: " << votosD + votosC << endl;
}

// Recorrido
void mostrarVotosPartido(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]){
	int votosEmitidos = 0;
	for (int i = 0; i < NumPartidos; i++){
		int sum = 0;
		for (int j = 0; j < NumCirc; j++){
			sum += arrayCirc[j].votos[i];
		}
		votosEmitidos += sum;
		cout << "Votos del partido " << arrayPartidos[i].nombrePartido << " : " << sum << endl;
	}
	cout << "Votos emitidos : " << votosEmitidos << endl;
}

// Carga desde ficheros
bool cargar(tPartido arrayPartidos[NumPartidos], tCirc arrayCirc[NumCirc]){
	ifstream archivo("datos.txt");
	tPartido varPartido;
	bool retorno = true;
	if (archivo.is_open()){
		for (int i = 0; i < NumPartidos; i++){
			archivo >> varPartido.nombrePartido >> varPartido.ideolog >> varPartido.polTerritorial;
			arrayPartidos[i] = varPartido;
		}
		for (int i = 0; i < NumCirc; i++){
			archivo >> arrayCirc[i].nombreCirc;
			for (int j = 0; j < NumPartidos; j++){
				archivo >> arrayCirc[i].votos[j];
			}
		}
		archivo.close();
	}
	else{
		cout << "No se ha encontrado el fichero datos.txt" << endl;
		retorno = false;
	}
	return retorno;
}
