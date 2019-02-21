#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ll n, m, a, b; cin >> n >> m >> a >> b;

	ll div = n % m;

	ll down = div * b; 
	ll up = (m - div) * a;

	ll ans = min(up, down);

	cout << ans << endl;

	return 0;
}
