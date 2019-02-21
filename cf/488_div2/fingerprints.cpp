#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<int> pass;
	set<int> finger;

	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		pass.push_back(x);
	}

	for (int i = 0; i < m; i++) {
		int x; cin >> x;
		finger.insert(x);
	}

	vector<int> ans;

	for (int i = 0; i < n; i++) {
		if (finger.find(pass[i]) != finger.end()) {
			ans.push_back(pass[i]);
		}
	}

	for (int i : ans) {
		cout << i << " ";
	}

	cout << "\n";

	return 0;
}
