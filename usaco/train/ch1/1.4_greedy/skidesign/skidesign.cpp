/*
ID: aaryan.1
TASK: skidesign
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");

	int n; fin >> n;
	vector<int> slopes;

	for (int i = 0; i < n; i++) {
		int x; fin >> x;
		slopes.push_back(x);
	}

	sort(slopes.begin(), slopes.end());
	
	int min = slopes[0];
	int max = slopes[slopes.size() - 1];

	int ans = 2000000000;

	for (int i = min; i < max - 16; i++) {
		int val = 0;
		for (int j = 0; j < n; j++) {
			if (slopes[j] < i) {
				val += (slopes[j] - i) * (slopes[j] - i);
			} else if (slopes[j] > (i + 17)) {
				val += (slopes[j] - i - 17) * (slopes[j] - i - 17);
			}
		}

		//cout << val << endl;

		if (val < ans) {
			ans = val;
		}
	}

	fout << ans << endl;
	
	return 0;
}



