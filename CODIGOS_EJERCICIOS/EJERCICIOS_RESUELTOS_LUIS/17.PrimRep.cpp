//Luis Pozas y Pablo Alvarez

#include <iostream>
#include <string>
using namespace std;

int main() {
	int num1;
	string palabra;
	cin >> palabra;

	while (palabra != "XXX") {
		num1 = palabra.size() - 2;

		for (int i = 0; i <= num1; i++) {
			if (palabra[i] == palabra[i + 1]) {
				cout << i << endl;
				i = num1;
			}
			else if ((palabra[i] != palabra[i + 1]) && (i == num1)) {
				cout << "NO" << endl;
			}
		}
		if (num1 == -1) {
			cout << "NO" << endl;
		}
	
		cin >> palabra;
	}

	return 0;
}
