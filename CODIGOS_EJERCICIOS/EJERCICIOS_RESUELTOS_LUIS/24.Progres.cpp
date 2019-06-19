//LUIS POZAS Y PABLO ALVAREZ
#include <iostream>
#include <string>
using namespace std;


int main() {
	int numcasos, num1, num2 = 0;

	cin >> numcasos;
	for (int i = 0; i < numcasos; i++) {
		cin >> num1;
		for (int j = 0; j < num1; j++) {
			for (int k = 0; k < num1; k++) {
				num2 = num2 + ((k + 1) * (j + 1));
				cout << ((k+1) * (j+1)) << " ";
			}
			cout << num2 << endl;
			num2 = 0;
		}
		cout << endl;
	}
	return 0;
}