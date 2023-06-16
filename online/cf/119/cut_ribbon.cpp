#include <iostream>
#include <algorithm>

using namespace std;

int nums[4001];
int cut[3];

int main() {
	int n; cin >> n >> cut[0] >> cut[1] >> cut[2];
	
	nums[cut[0]] = 1;
	nums[cut[1]] = 1;
	nums[cut[2]] = 1;
	
	for (int i = cut[0]; i <= n; i++) {
		if (nums[i - cut[0]] != 0) {
			int val = nums[i - cut[0]] + 1;
			nums[i] = nums[i] > val ? nums[i] : val;
		}
	}

	for (int i = cut[1]; i <= n; i++) {
		if (nums[i - cut[1]] != 0) {
			int val = nums[i - cut[1]] + 1;
			nums[i] = nums[i] > val ? nums[i] : val;
		}
	}
	
	for (int i = cut[2]; i <= n; i++) {
		if (nums[i - cut[2]] != 0) {
			int val = nums[i - cut[2]] + 1;
			nums[i] = nums[i] > val ? nums[i] : val;
		}
	}
	
	cout << nums[n] << '\n';
	return 0;
}