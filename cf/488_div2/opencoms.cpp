#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

int common(pair<int, int> x, pair<int, int> y) {
	int ans = 0;
	if (x.first == y.first) ans++;
	if (x.first == y.second) ans++;
	if (x.second == y.first) ans++;
	if (x.second == y.second) ans++;

	return ans;
}

vector<int> findCommon(pair<int, int> x, pair<int, int> y) {
	vector<int> ans(2);
	if (x.first == y.first) ans = {0, 0};
	if (x.first == y.second) ans = {0, 1};
	if (x.second == y.first) ans = {1, 0};
	if (x.second == y.second) ans = {1, 1};

	return ans;
}

int main() {
	int n, m; cin >> n >> m;
	vector<pair<int, int>> f;
	vector<pair<int, int>> s;

	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		f.push_back(make_pair(x, y));
	}

	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		s.push_back(make_pair(x, y));
	}

	vector<pair<int, int>> fCount(n, {0, 0});
	vector<pair<int, int>> sCount(m, {0, 0});

	int totalOne = 0;
	int ans = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (common(f[i], s[j]) == 1) {
				//cout << "*" << i << j << endl;
				totalOne++;
				vector<int> val = findCommon(f[i], s[j]);
				if (val[0] == 0) {
					fCount[i].first++;
					ans = f[i].first;
				} else {
					fCount[i].second++;
					ans = f[i].second;
				}

				if (val[1] == 0) {
					sCount[j].first++;
				} else {
					sCount[j].second++;
				}
			}
		}
	}

	//cout << totalOne << endl;

	if (totalOne == 1) {
		cout << ans << "\n";
	} else if (totalOne > 1) {
		bool bad = false;
		for (int i = 0; i < n; i++) {
			//cout << fCount[i].first << "!" << fCount[i].second << endl;
			if (fCount[i].first > 0 && fCount[i].second > 0) {
				bad = true;
				break;
			}
		}

		for (int i = 0; i < m; i++) {
			if (sCount[i].first > 0 && sCount[i].second > 0) {
				bad = true;
				break;
			}
		}

		if (bad) {
			cout << "-1\n";
		} else {
			cout << "0\n";
		}

	} else {
		cout << "-1\n";
	}

	return 0;
}
