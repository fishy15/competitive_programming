#include <iostream>
#include <algorithm>

using namespace std;

int gcd(int x, int y) {
	if (x == 0) {
		return y;
	} else if (y == 0) : (y < x) {
		return gcd(y, x);
	}

	return gcd(x, y % x);
}

int main() {
	int a, b, x, y; cin >> a >> b >> x >> y;
	int count = 0;
	for (int i = a; i <= b; i++) {
		if (y % i != 0) {
			continue;
		}

		int j = x*y / i;
		if (j < a || j > b) {
			continue;
		}

		if (gcd(i, j) == x) {
			count++;
		}
	}

	cout << count << endl;
}
