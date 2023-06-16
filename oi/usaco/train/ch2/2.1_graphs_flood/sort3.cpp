/*
ID: aaryan.1
TASK: sort3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
	ifstream fin("sort3.in");
	ofstream fout("sort3.out");

	int n; fin >> n;
	vector<int> nums;
	vector<int> c(4, 0);
	int ans = 0;

	for (int i = 0; i < n; i++) {
		int x; fin >> x;
		nums.push_back(x);
		c[x]++;
	}

	vector<vector<int>> counts(4, vector<int>(4, 0));

	for (int i = 0; i < n; i++) {
		if (i < c[1]) {
			counts[nums[i]][1]++;
		} else if (i < c[1] + c[2]) {
			counts[nums[i]][2]++;
		} else {
			counts[nums[i]][3]++;
		}
	}

	for (int i = 1; i < 3; i++) {
		for (int j = i + 1; j <= 3; j++) {
			int mini = min(counts[i][j], counts[j][i]);
			counts[i][j] -= mini;
			counts[j][i] -= mini;
			ans += mini;
		}
	}

	int temp = 0;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (i != j) {
				temp += counts[i][j];
			}
		}
	}

	ans += temp / 3 * 2;

	fout << ans << "\n";

	return 0;
}

