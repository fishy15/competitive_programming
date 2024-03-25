#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> factors(int x) {
	vector<int> fs;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			fs.push_back(i);
			fs.push_back(x / i);
		}
	}
	return fs;
}

void solve() {
	int w, l;
	cin >> w >> l;
	
	set<int> res;
	for (auto x : factors(gcd(w - 1, l - 1))) {
		res.insert(x);
	}
	for (auto x : factors(gcd(w - 2, l))) {
		res.insert(x);
	}
	for (auto x : factors(gcd(w, l - 2))) {
		res.insert(x);
	}
	
	if (w % 2 != l % 2) {
		res.insert(2);
	}
	
	cout << res.size() << ' ';
	for (auto x : res) {
		cout << x << ' ';
	}
	cout << '\n';
}

int main() {
  	ios_base::sync_with_stdio(false);
  	cin.tie(NULL);
	int t; cin >> t;
	while (t--) {
		solve();
	}
}
