//LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;

const int MAX = 100000;
typedef int tArray[MAX];

int main() {
	int numcasos;
	string palabra;

	cin >> numcasos;
	cin.ignore();

	for (int i = 0; i < numcasos; i++) {
		getline(cin, palabra);
		cout << palabra.size() <<" ";
		for (int j = palabra.size()-1; j >= 0; j--) {
			palabra[j] = toupper(palabra[j]);
			cout << palabra[j];
		}
		cout << endl;
	}
	return 0;
}