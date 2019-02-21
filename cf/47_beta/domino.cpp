#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	int ans1 = (n / 2 * m);
	if (n % 2 == 1) {
		ans1 += m / 2;
	}

	int ans2 = (m / 2 * n);
	if (m % 2 == 1) {
		ans2 += n / 2;
	}

	cout << max(ans1, ans2) << '\n';

	return 0;
}
