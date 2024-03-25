#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int nxt_d(int x) {
	x++;
	if (x >= 360) x -= 360;
	return x;
}

int prev_d(int x) {
	x--;
	if (x < 0) x += 360;
	return x;
}

void solve() {
	int n;
	cin >> n;
	
	// {r, t} represents radius r -> r+1, degree t -> t+1
	vector vis(25, vector(360, false));

	vector move_in(25, vector(360, true));
	vector move_out(25, vector(360, true));
	vector move_sub(25, vector(360, true));
	vector move_add(25, vector(360, true));
	
	// can't  leave
	for (int t = 0; t < 360; t++) {
		move_in[0][t] = false;
		move_out[24][t] = false;
	}
	
	for (int i = 0; i < n; i++) {
		char typ;
		cin >> typ;
		if (typ == 'C') {
			int r, t1, t2;
			cin >> r >> t1 >> t2;
			for (int t = t1; t != t2; t = nxt_d(t)) {
				move_out[r - 1][t] = false;
				move_in[r][t] = false;
			}
		} else {
			int r1, r2, t;
			cin >> r1 >> r2 >> t;
			for (int r = r1; r < r2; r++) {
				move_sub[r][t] = false;
				move_add[r][prev_d(t)] = false;
			}
		}
	}
	
	queue<pair<int, int>> q;
	for (int t = 0; t < 360; t++) {
		vis[0][t] = true;
		q.push({0, t});
	}
	
	while (!q.empty()) {
		auto [r, t] = q.front();
		q.pop();
		
		if (r == 24) {
			cout << "YES\n";
			return;
		}
		
		auto process = [&](int nr, int nt) {
			if (!vis[nr][nt]) {
				vis[nr][nt] = true;
				q.push({nr, nt});
			}
		};
		
		if (move_in[r][t]) process(r - 1, t);
		if (move_out[r][t]) process(r + 1, t);
		if (move_add[r][t]) process(r, nxt_d(t));
		if (move_sub[r][t]) process(r, prev_d(t));
	}
	
	cout << "NO\n";
}
 
int main() {
  	ios_base::sync_with_stdio(false);
  	cin.tie(NULL);
	int t; cin >> t;
	while (t--) {
		solve();
	}
}
