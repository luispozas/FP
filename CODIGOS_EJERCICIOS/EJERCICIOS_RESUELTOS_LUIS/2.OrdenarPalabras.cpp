//Luis Pozas
//Pablo Alvarez

#include <iostream>
#include <string>
using namespace std;


int main()
{
	string palabra1, palabra2, palabra3;
	int num1;

	//cout << "Dame un numero" << endl;
	cin >> num1;

	for (int i = 0; i < num1; ++i) {
		//cout << "Dame tres palabras" << endl;
		cin >> palabra1;
		cin >> palabra2;
		cin >> palabra3;

		if (palabra1 < palabra2) {
			if (palabra2 < palabra3) {
				cout << palabra1 << "," << palabra2 << "," << palabra3 << endl;
			}
			else if (palabra1 < palabra3) {
				cout << palabra1 << "," << palabra3 << "," << palabra2 << endl;
			}
			else {
				cout << palabra3 << "," << palabra1 << "," << palabra2 << endl;
			}
		}
		else
			if (palabra1 < palabra3) {
				cout << palabra2 << "," << palabra1 << "," << palabra3 << endl;
			}
			else if (palabra3 < palabra2) {
				cout << palabra3 << "," << palabra2 << "," << palabra1 << endl;
			}
			else {
				cout << palabra2 << "," << palabra3 << "," << palabra1 << endl;
			}
	}

	return 0;

}
