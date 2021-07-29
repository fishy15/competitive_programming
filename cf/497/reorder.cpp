#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int roundUpHalf(int x) {
	if (x % 2 == 0) {
		return x / 2;
	}
	return x / 2 + 1;
}

int main() {
	int n; cin >> n;
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		nums.push_back(x);
	}

	sort(nums.begin(), nums.end());

	int ans = 0;

	int i = 0;
	while (nums[i] <= nums[ans] && i < n) {
		i++;
	}

	for (int j = i; j < n; j++) {
		//cout << j << endl;
		if (nums[j] > nums[ans]) {
			ans++;
		}
	}

	cout << ans << '\n';
	return 0;
}
