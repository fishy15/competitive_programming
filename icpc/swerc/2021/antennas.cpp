#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
struct merge_sort_tree {
	struct node {
		// {endpoint, index}
		// sorted in increasing order left
		// sorted in decreasing order right
		vector<pair<int, int>> left;
		vector<pair<int, int>> right;
	
		node comb(const node &other) const {
			int sz = left.size() + other.left.size();
			vector<pair<int, int>> new_left(sz), new_right(sz);
			merge(
				left.begin(), left.end(),
				other.left.begin(), other.left.end(),
				new_left.begin(),
				greater<>{}
			);
			merge(
				right.begin(), right.end(),
				other.right.begin(), other.right.end(),
				new_right.begin()
			);
			return node{new_left, new_right};
		}
	};
	
	int n;
	vector<node> st;
	vector<bool> done;
	
	merge_sort_tree(const vector<int> &p) {
		n = p.size();
		st = vector<node>(4 * n);
		done = vector<bool>(n);
		build(1, 0, n - 1, p);
	}
	
	void build(int v, int l, int r, const vector<int> &p) {
		if (l == r) {
			vector<pair<int, int>> left = {{l - p[l], l}};
			vector<pair<int, int>> right = {{l + p[l], l}};
			st[v] = node{left, right};
		} else {
			int m = (l + r) / 2;
			build(2 * v, l, m, p);
			build(2 * v + 1, m + 1, r, p);
			st[v] = st[2 * v].comb(st[2 * v + 1]);
		}
	}
	
	// all centers that haven't been processed, in [x, y], and includes `include` on the left
	vector<int> query_left(int x, int y, int include) {
		return query_left(1, 0, n - 1, x, y, include);
	}
	vector<int> query_left(int v, int l, int r, int x, int y, int include) {
		if (x <= l && r <= y) {
			auto &cur = st[v].left;
			vector<int> res;
			while (!cur.empty()) {
				auto [lx, center] = cur.back();
				if (done[center]) {
					cur.pop_back();
				} else if (lx <= include) {
					res.push_back(center);
					done[center] = true;
					cur.pop_back();
				} else {
					break;
				}
			}
			return res;
		} else if (r < x || y < l) {
			return {};
		} else {
			int m = (l + r) / 2;
			auto v1 = query_left(2 * v, l, m, x, y, include);
			auto v2 = query_left(2 * v + 1, m + 1, r, x, y, include);
			for (auto x : v2) {
				v1.push_back(x);
			}
			return v1;
		}
	}
	
	// all centers that haven't been processed, in [x, y], and includes `include` on the right
	vector<int> query_right(int x, int y, int include) {
		return query_right(1, 0, n - 1, x, y, include);
	}
	vector<int> query_right(int v, int l, int r, int x, int y, int include) {
		if (x <= l && r <= y) {
			auto &cur = st[v].right;
			vector<int> res;
			while (!cur.empty()) {
				auto [rx, x] = cur.back();
				if (done[x]) {
					cur.pop_back();
				} else if (include <= rx) {
					res.push_back(x);
					done[x] = true;
					cur.pop_back();
				} else {
					break;
				}
			}
			return res;
		} else if (r < x || y < l) {
			return {};
		} else {
			int m = (l + r) / 2;
			auto v1 = query_right(2 * v, l, m, x, y, include);
			auto v2 = query_right(2 * v + 1, m + 1, r, x, y, include);
			for (auto x : v2) {
				v1.push_back(x);
			}
			return v1;
		}
	}
};
 
void solve() {
	int n, a, b;
	cin >> n >> a >> b;
	a--;
	b--;
	
	vector<int> p(n);
	for (auto &x : p) {
		cin >> x;
	}
	
	auto st = merge_sort_tree(p);
	st.done[a] = true;
	vector dist(n, n);
	vector vis(n, false);
	
	dist[a] = 0;
	vis[a] = true;
	
	queue<int> q;
	q.push(a);
	
	while (!q.empty()) {
		auto v = q.front();
		q.pop();
		
		for (auto x : st.query_right(v - p[v], v, v)) {
			if (!vis[x]) {
				vis[x] = true;
				dist[x] = dist[v] + 1;
				q.push(x);
			}
		}
		
		for (auto x : st.query_left(v, v + p[v], v)) {
			if (!vis[x]) {
				vis[x] = true;
				dist[x] = dist[v] + 1;
				q.push(x);
			}
		}
	}
	
	cout << dist[b] << '\n';
}

int main() {
  	ios_base::sync_with_stdio(false);
  	cin.tie(NULL);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
