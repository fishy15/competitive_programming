#include <iostream>
#include <string>

using namespace std;

int main() {
	int a, b, x; cin >> a >> b >> x;
	string ans = "";
	for (int i = 0; i < x; i++) {
		if (i % 2 == 0) {
			ans += '0';
		} else {
			ans += '1';
		}

		a--;
		b--;
	}

	for (int i = 0; i < a; i++) {
		ans += '0';
	}

	for (int i = 0; i < b; i++) {
		ans += '1';
	}

	cout << ans << '\n';

	return 0;
}
