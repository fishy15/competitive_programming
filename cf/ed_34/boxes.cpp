#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

int main() {
	int n; cin >> n;
	map<int, int> nums;
	int max = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (nums.find(x) == nums.end()) {
			nums.insert(make_pair(x, 1));
		} else {
			nums[x]++;
		}

		if (nums[x] > max ) {
			max = nums[x];
		}
	}

	cout << max << '\n';

	return 0;
}
