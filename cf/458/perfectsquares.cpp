#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		int q; cin >> q;
		nums.push_back(q);
	}

	sort(nums.begin(), nums.end());

	for (int i = n - 1; i >= 0; i--) {
		if (sqrt(nums[i]) != (int)(sqrt(nums[i]))) {
			cout << nums[i] << endl;
			break;
		} 
	}

	return 0;
}
