//Luis Pozas
//Pablo Alvarez

#include <iostream>
using namespace std;


int main()
{
	int num1, n1, n2, n3;

	//cout << "Dame un numero" << endl;
	cin >> num1;

	for (int i = 0; i < num1; ++i) {
		//cout << "Dame dos numeros" << endl;
		cin >> n1;
		cin >> n2;
		
		n3 = (n2 - n1 + 1)*(n1 + n2) / 2;

		cout << n3 << endl;





	}

	return 0;
}