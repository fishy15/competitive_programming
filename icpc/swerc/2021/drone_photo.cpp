#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int main() {
  	ios_base::sync_with_stdio(false);
  	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vector grid(n, vector<int>(n));
	vector at(n * n, pair<int, int>{});
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			grid[i][j]--;
			at[grid[i][j]] = {i, j};
		}
	}
	
	vector<int> row_cnt(n), col_cnt(n);
	ll invalid = 0;
	for (int i = 0; i < n * n; i++) {
		auto [x, y] = at[i];
		invalid += (ll) row_cnt[x] * col_cnt[y];
		row_cnt[x]++;
		col_cnt[y]++;
	}
	
	ll choose2 = (ll) n * (n - 1) / 2;
	ll total = choose2 * choose2;
	
	invalid -= total;
	cout << (total - invalid) << '\n';
	
	return 0;
}
