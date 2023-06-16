#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		nums.push_back(x);
	}

	int min = 1000000000;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int minx = max(nums[i] - i, 0);
		if (minx % n > 0) {
			minx = minx / n + 1;
		} else {
			minx /= n;
		}

		minx = n * minx + i;

		if (minx < min) {
			min = minx;
			ans = i + 1;
		}
	}
		
	cout << ans << "\n";

	return 0;
}
