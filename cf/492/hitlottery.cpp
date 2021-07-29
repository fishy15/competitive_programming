#include <iostream>

using namespace std;

int main() {
	int n; cin >> n;
	int ans = 0;
	if (n >= 100) {
		ans += n / 100;
		n = n % 100;
	}

	//cout << n << endl;

	if (n >= 20) {
		ans += n/20;
		n = n % 20;
	}
	//cout << n << endl;
	if (n >= 10) {
		ans += n/10;
		n = n % 10;
	}
	//cout << n << endl;
	if (n >= 5) {
		ans += n/5;
		n = n%5;
	}
	//cout << n << endl;
	ans += n;

	cout << ans << "\n";

	return 0;
}
