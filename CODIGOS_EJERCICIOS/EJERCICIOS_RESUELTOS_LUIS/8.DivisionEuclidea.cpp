//Luis Pozas
//Pablo Alvarez

#include <iostream>
using namespace std;

int main()
{
	int num1, a, b, q, r;

	cin >> num1;

	for (int i = 0; i < num1; ++i) {

		cin >> a;
		cin >> b;


		if (b == 0) {
			cout << "DIV0" << endl;
		}
		else {
			if (a > 0) {

				q = a / b;
				r = a % b;
				cout << q << " " << r << endl;
			}
			else {
				if (a <= 0) {
					if (b < 0) {

						r = (a%b - b) % b;
						q = ((a - r) / b);
						cout << q << " " << r << endl;
					}
					else {
						r = (a % b + b) % b;
						q = (a - r) / b;
						cout << q << " " << r << endl;
					}
				}
			}

		}
			
	}

	return 0;
}