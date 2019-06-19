//Luis Pozas y Pablo Alvarez

#include <iostream>
#include <string>
using namespace std;
const int MAX = 100000;

typedef float miArray[MAX];

int main() {

	int a, p1, contador1, contador2;
	float media, sumador;
	cin >> a;

	miArray p2;

	for (int i = 0; i < a; i++) {
		cin >> p1;
		sumador = 0;
		contador1 = 0, contador2 = 0;

		for (int j = 0; j <= MAX; j++) {

			cin >> p2[j];

			if (p2[j] != 0) {
				sumador = sumador + p2[j];
				media = sumador / (j + 1);
			}
			else if (p2[j] == 0) {
				j = MAX + 1;
			}

		}
		for (int m = 0; m <= MAX; m++) {

			if (p2[m] != 0) {
				if (p2[m] >= media) { contador1++; }
				if (p2[m] < media) { contador2++; }
			}
			else if (p2[m] == 0) {
				m = MAX + 1;
			}
		}

		if (p1 >= media) {
			cout << "MAYOR " << contador1 << endl;
		}
		else if (p1 < media) {
			cout << "MENOR " << contador2 << endl;
		}
	}
return 0;
}

