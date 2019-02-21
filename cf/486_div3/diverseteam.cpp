#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<pair<int, int>> nums;
	for (int i = 1; i <= n; i++) {
		int v; cin >> v;
		pair<int, int> x = {v, i};
		nums.push_back(x);
	}

	sort(nums.begin(), nums.end());

	vector<int> ans;
	ans.push_back(nums[0].second);
	int count = 1;
	for (int i = 1; i < n; i++) {
		if (nums[i].first != nums[i - 1].first) {
			count++;
			ans.push_back(nums[i].second);
		}

		if (count >= k) {
			break;
		}
	}

	if (ans.size() >= k) {
		cout << "YES\n";
		for (int i = 0; i < ans.size(); i++) {
			cout << ans[i] << " ";
		}
	} else {
		cout << "NO";
	}

	cout << "\n";
}
