#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int nums[1000];

int main() {
	int n; cin >> n;
	
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	
	int ans = 0x3f3f3f3f;
	int ans_val = 0;
	
	for (int k = 1; k <= 100; k++) {
		int sum = 0;	
		for (int i = 0; i < n; i++) {
			int min = 0x3f3f3f3f;
			for (int j = -1; j <= 1; j++) {
				int val = abs(nums[i] - (k + j));
				if (val < min) min = val;
			}
			
			sum += min;
		}
		
		if (sum < ans) {
			ans_val = k;
			ans = sum;
		}
	}
	
	cout << ans_val << ' ' << ans << '\n';
	return 0;
}