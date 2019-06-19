/* LUIS POZAS Y PABLO ALVAREZ */

#include <iostream>
#include <string>
using namespace std;

int main() {
	int num1, n = 0;
	string palabra;
	bool a = false, e = false, i = false, o = false, u = false;
	cin >> num1;
	while (n < num1) {
		cin >> palabra;
		a = false, e = false, i = false, o = false, u = false;
		for (int j = 0; j < palabra.length(); j++) {

			if (palabra[j] == 'a') {
				a = true;
			}
			else if (palabra[j] == 'e') {
				e = true;
			}
			else if (palabra[j] == 'i') {
				i = true;
			}
			else if (palabra[j] == 'o') {
				o = true;
			}
			else if (palabra[j] == 'u') {
				u = true;
			}
		}

		if ((a == true) && (e == true) && (i == true) && (o == true) && (u == true)) {
			cout << "SI" << endl;
		}
		else { cout << "NO" << endl; }

		n++;
	}
	return 0;
}