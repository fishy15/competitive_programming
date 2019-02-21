#include <iostream>

using namespace std;

typedef unsigned long long ull;

int MOD = 1000000007;

/*
ll mod(ll x) {
	ll mod = x % MOD;
	while (mod < 0) {
		mod += MOD;
	}

	return mod;
}
*/

int main() {
	ull x, k; cin >> x >> k;
	ull mid = (2 * x - 1) % MOD;

	mid = mid << k;
	mid = mid % MOD;

	if (x == 0) {
		cout << "0\n";
	} else {
		cout << (mid + 1) % MOD << "\n";
	}
	return 0;
}
