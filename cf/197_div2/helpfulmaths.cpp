#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> nums;
	string s;
	
	cin >> s;
	
	for (int i = 0; i < s.size(); i++) {
		if (isdigit(s[i])) {
			nums.push_back(s[i] - '0');
		}
	}
	
	sort(nums.begin(), nums.end());
	
	string ans;
	for (int i = 0; i < nums.size(); i++) {
		ans += (nums[i] + '0');
		if (i != nums.size() - 1) {
			ans += '+';
		}
	}
	
	cout << ans << endl;
}
