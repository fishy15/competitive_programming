#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	int n; cin >> n;

	// 0 = left, 1 = upright, 2 = right
	vector<vector<int> > nums(n, vector<int>(3, -1));
	vector<pair<int, int> > trees;
	
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		trees.push_back(make_pair(a, b));
	}

	if (n < 2) {
		cout << n << '\n';
		return 0;
	}
	
	nums[0][0] = 1;
	nums[0][1] = 0;
	
	if (trees[1].first > trees[0].first + trees[0].second) {
		nums[0][2] = 1;
	}
	
	for (int i = 1; i < n; i++) {
		int maxPrev = max(max(nums[i - 1][0], nums[i - 1][1]), nums[i - 1][2]);
		if (trees[i].first - trees[i].second > trees[i - 1].first + trees[i - 1].second) {
			nums[i][0] = maxPrev + 1;
		} else if (trees[i].first - trees[i].second > trees[i - 1].first) {
			nums[i][0] = (max(nums[i - 1][0], nums[i - 1][1])) + 1;
		}
		
		nums[i][1] = maxPrev;
		
		if (i == n - 1 || trees[i].first + trees[i].second < trees[i + 1].first) {
			nums[i][2] = maxPrev + 1;
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			//cout << nums[i][j] << ' ';
			ans = nums[i][j] > ans ? nums[i][j] : ans;
		}
		
		//cout << endl;
	}
	
	cout << ans << '\n';
	return 0;
}