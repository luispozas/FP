//Luis Pozas
//Pablo Álvarez

#include <iostream>
using namespace std;


int main() {

	int num1, i, n1, n2, n3, n4;
	cin >> num1;
	i = 0;

	while (i < num1) {

		cin >> n1;
		cin >> n2;
		cin >> n3;
		cin >> n4;

		if (1 <= n1, n2, n3, n4 <= 6) {
			if ((n1 + n2) > (n3 + n4)){
				cout << "JORGE" << " " << n1 + n2 << " " << "ANA" << " " << n3 + n4 << endl;
			}
			else if ((n1 + n2) < (n3 + n4)) {
				cout << "ANA" << " " << n3 + n4 << " " << "JORGE" << " " << n1 + n2 << endl;
			}
			else {
				cout << "EMPATE" << " " << n1 + n2 << endl;
			}
		}

		i++;
	}

	return 0;
}