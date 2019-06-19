//Luis Pozas y Pablo Alvarez

#include <iostream>
using namespace std;


int main() {

	int a, b, r = 0, auxa = 0, auxb = 0;

	cin >> a;
	cin >> b;

	while ((a != 0) && (b != 0)){
		
		r = (a % b);
		while (r != 0){
			a = b;
			b = r;
			r = (a % b);

		}

		if (r == 0){
			cout << b << endl;
		}

		cin >> a;
		cin >> b;
	}
	return 0;
}