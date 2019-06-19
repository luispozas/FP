//LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;

typedef bool vector[100001];

int main() {
	int numtotal;
	vector numeros;

	cin >> numtotal;

	if (numtotal <= 100000) {
		numeros[0] = false;
		numeros[1] = false;

		for (int j = 2; j <= numtotal; j++) {
			numeros[j] = true;
		}

		for (int i = 2; i*i <= numtotal; i++) {
			for (int j = i + 1; j <= numtotal; j++){
				if (j % i == 0 && numeros[j]){
					numeros[j] = false;
				}
			}
		}

		for (int i = 0; i <= numtotal; i++){
			if (numeros[i]){
				cout << i << endl;
			}
		}
	}
	return 0;

}