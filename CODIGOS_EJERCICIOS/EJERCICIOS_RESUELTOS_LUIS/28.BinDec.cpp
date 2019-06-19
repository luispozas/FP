//LUIS POZAS PALOMO
#include <iostream>
#include <string>
using namespace std;

int main() {
	long long int num1;
    string bin;

	cin >> num1;

	for (int i = 0; i < num1; i++) {
		cin >> bin;
		unsigned long long int  res = 1, cont = 0, aux = 0;

		for (int i = bin.length()-1; i >= 0; i--) {
			if (bin[i] == '1') {
				if (cont == 0) { aux++; }
				else {
					for (int j = 0; j < cont; j++) {
						res = 2 * res;
					}
					aux = aux + res;
					res = 1;
				}
					cont++;
			}
			else { cont++; }
		}
		cout << aux << endl;

	}
	return 0;
}