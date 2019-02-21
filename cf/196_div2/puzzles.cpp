#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<int> sz;

	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		sz.push_back(x);
	}

	sort(sz.begin(), sz.end());

	int min = 5000;

	for (int i = n - 1; i < m; i++) {
		//cout << sz[i] - sz[i - 4] << endl;
		if (sz[i] - sz[i - n + 1] < min) {
			min = sz[i] - sz[i - n + 1];
		}
	}

	cout << min << '\n';

	return 0;
}

