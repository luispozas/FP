//Pablo Álvarez
//Luis Pozas

#include <iostream>
using namespace std;

int main() {

	int num1, i, n1;
	cin >> num1;
	i = 0;

	while (i < num1) {

		cin >> n1;
		
		if (((n1 % 4 == 0) && (n1 % 100 != 0)) || ((n1 % 100 == 0) && (n1 % 400 == 0))) {
			cout << "SI" << endl;
		}
		else cout << "NO" << endl; 

		i++;

	}

	return 0;

}