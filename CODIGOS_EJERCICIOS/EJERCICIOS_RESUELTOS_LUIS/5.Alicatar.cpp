//Luis Pozas
//Pablo Alvarez

#include <iostream>;
using namespace std;

int main() {

	int num1, i, p1, p2, a1, a2, naux1, naux2;
	int n1, n2;
	i = 0;
	cin >> num1;

	while (i < num1) {
		cin >> p1;
		cin >> p2;
		cin >> a1;
		cin >> a2;
		n2 = p2 / a2;
		n1 = p1 / a1;

		if ((p2 % a2 == 0) && (p1 % a1 == 0)) {
			cout << n1*n2 << endl;
		}

		else {
			if ((p2 % a2 != 0) && (p1 % a1 == 0)) {

				naux2 = n2 + 1;
				cout << n1 * naux2 << " " << "NECESITA COMPRAR MAQUINA" << endl;

			}
			else {
				if ((p1 % a1 != 0) && (p2 % a2 == 0)) {

					naux1 = n1 + 1;
					cout << n2*naux1 << " " << "NECESITA COMPRAR MAQUINA" << endl;
				}
				else {
					if ((p1 % a1 != 0) && (p2 % a2 != 0)) {
						naux2 = n2 + 1;
						naux1 = n1 + 1;
						cout << naux1*naux2 << " " << "NECESITA COMPRAR MAQUINA" << endl;
					}

				}
			}

		}

		i++;
	}

	return 0;

}