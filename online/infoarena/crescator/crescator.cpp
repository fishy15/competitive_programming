#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool checkVec(vector<bool> v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i]) {
			return true;
		}
	}

	return false;
}

int main() {
	ifstream fin("crescator.in");
	ofstream fout("crescator.out");

	int n; fin >> n;
	vector<int> nums(n - 1);

	for (int i = 0; i < n; i++) {
		fin >> nums[i];
	}

	int len = 2;
	int maxLen = 0;
	int count = n; // size 1
	vector<bool> curVec;

	for (int i = 0; i < n - 1; i++) {
		if (nums[i] < nums[i + 1]) {
			curVec.push_back(true);
			count++;
		} else {
			curVec.push_back(false);
		}
	}

	while (checkVec(curVec)) {
		maxLen = len;
		vector<bool> newVec;

		for (int i = 0; i < n - len + 1; i++) {
			if (curVec[i] && curVec[i + 1]) {
				newVec.push_back(true);
                count++;
				//cout << i << " to " << i + len << endl;
			} else {
				newVec.push_back(false);
			}
		}

		len++;
		curVec = newVec;
	}

	fout << count << ' ' << maxLen << '\n';
	return 0;
}
