#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

pair<ll, ll> solve(int n, const vector<int> &height) {
	vector<pair<int, int>> ord;
	for (int i = 0; i < n; i++) {
		ord.push_back({height[i], i});
	}

	sort(ord.rbegin(), ord.rend());

	set<int> seen;
	pair<ll, ll> ans = {0, 1};

	for (auto [h, i] : ord) {
		auto it = seen.insert(i).first;
		if (it != seen.begin()) {
			auto pi = *prev(it);
			int d = i - pi - 1;

			// what fraction of the way up are we
			int high = height[pi];
			int low = height[pi + 1];
			int dh = abs(high - low);
			int me_up = abs(h - low);
			int g = gcd(me_up, dh);

			pair<ll, ll> cur = {me_up / g, dh / g};
			cur.first += d * cur.second;

			if (ans.first * cur.second < cur.first * ans.second) {
				ans = cur;
			}
		}
	}

	return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int> height(n);
	for (int i = 0; i < n; i++) {
		cin >> height[i];
	}

	auto ans1 = solve(n, height);
	reverse(height.begin(), height.end());
	auto ans2 = solve(n, height);

	pair<ll, ll> ans;
	if (ans1.first * ans2.second > ans2.first * ans1.second) {
		ans = ans1;
	} else {
		ans = ans2;
	}

	if (ans.second == 1) {
		cout << ans.first << '\n';
	} else {
		cout << ans.first << '/' << ans.second << '\n';
	}

	return 0;
}
