#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#define ll long long

using namespace std;

int main() {
	int n; cin >> n;
	vector<pair<ll, ll> > lines;
	ll max = 0;
	for (int i = 0; i < n; i++) {
		ll x, y; cin >> x >> y;
		if (x < 0) {
			x = 0;
		}
		lines.push_back(make_pair(x, y));

		if (y > max) {
			max = y;
		}
	}

	vector<ll> points(max + 1, 0);

	for (int i = 0; i < n; i++) {
		for (ll j = lines[i].first; j <= lines[i].second; j++) {
			if (j < 0 || j >= max + 1) {
				continue;
			}

			points[j]++;
		}
	}

	vector<ll> ans(n, 0);

	for (ll i : points) {
		if (i > 0 && i <= ans.size()) {
			ans[i - 1]++;
		}
	}

	for (ll i : ans) {
		cout << i << ' ';
	}
	cout << '\n';

	return 0;
}
