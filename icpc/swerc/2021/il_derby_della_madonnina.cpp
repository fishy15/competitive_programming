#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct segtree {
	int n;
	vector<int> st;

	segtree(int n) : n(n), st(4 * n) {}
	
	void upd(int x, int y) { upd(1, 0, n - 1, x, y); }
	void upd(int v, int l, int r, int x, int y) {
		if (l == r) {
			st[v] = y;
		} else {
			int m = (l + r) / 2;
			if (x <= m) {
				upd(2 * v, l, m, x, y);
			} else {
				upd(2 * v + 1, m + 1, r, x, y);
			}
			st[v] = max(st[2 * v], st[2 * v + 1]);
		}
	}
	
	int qry(int x, int y) { return qry(1, 0, n - 1, x, y); }
	int qry(int v, int l, int r, int x, int y) {
		if (x <= l && r <= y) {
			return st[v];
		} else if (r < x || y < l) {
			return 0;
		} else {
			int m = (l + r) / 2;
			return max(
				qry(2 * v, l, m, x, y),
				qry(2 * v + 1, m + 1, r, x, y)
			);
		}
	}
};

vector<pair<int, int>> compress(vector<pair<ll, ll>> kicks) {
	vector<ll> xs, ys;
	for (auto [x, y] : kicks) {
		xs.push_back(x);
		ys.push_back(y);
	}
	
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	
	auto lb = [&](auto &v, auto x) {
		return lower_bound(v.begin(), v.end(), x) - v.begin();
	};
	
	vector<pair<int, int>> res;
	for (int i = 0; i < (int) kicks.size(); i++) {
		res.push_back({
			lb(xs, kicks[i].first),
			lb(ys, kicks[i].second)
		});
	}
	
	return res;
}

vector<pair<ll, ll>> delete_unreachable(const vector<pair<ll, ll>> kicks) {
	vector<pair<ll, ll>> res;
	for (auto [x, y] : kicks) {
		if (x >= abs(y)) {
			res.push_back({x, y});
		}
	}
	return res;
}
 
int main() {
  	ios_base::sync_with_stdio(false);
  	cin.tie(NULL);
	
	int n, v;
	cin >> n >> v;
	
	vector<pair<ll, ll>> kicks(n);
	for (int i = 0; i < n; i++) {
		cin >> kicks[i].first;
		kicks[i].first *= v;
	}
	for (int i = 0; i < n; i++) {
		cin >> kicks[i].second;
	}
	
	kicks = delete_unreachable(kicks);
	n = kicks.size();

	if (n == 0) {
		cout << "0\n";
		return 0;
	}
	
	// can assume v = 1 now
	// apply transformation (x, y) -> (x + y, x - y)
	// (x - 1, y + 1) -> (x + y, x - y - 2)
	// (x - 1, y - 1) -> (x + y - 2, x - y)
	// so we need to query points that are to the left & below
	
	for (auto &[x, y] : kicks) {
		tie(x, y) = tuple{x + y, x - y};
	}
	
	auto kicks_c = compress(kicks);
	sort(kicks_c.begin(), kicks_c.end());
	sort(kicks.begin(), kicks.end());
	
	segtree st(n);
	
	for (auto [x, y] : kicks_c) {
		auto p = st.qry(0, y);
		st.upd(y, p + 1);
	}
	
	cout << st.qry(0, n - 1) << '\n';
	return 0;
}
