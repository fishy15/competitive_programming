#include <iostream>

using namespace std;

int main() {
	cout << "hi\n";
	int n; cin >> n;
	int k = 0;
	int v = 0;
	int p = 0;
	cout << "hi\n";
	while (v < n / 2) {
		cout << "hi\n";
		cout << v << endl;
		cout << v << endl;
		k++;
		v = 0;
		p = 0;
		int c = n;
		while (c > 0) {
			cout << "V: " << v << endl;
			cout << "P: " << p << endl;
			cout << "C: " << c << endl;
			v += k;
			c -= k;
			p += c / 10;
			c -= c / 10;
		}
	}

	cout << k << endl;

	return 0;
}
