/*
ID: aaryan.1
TASK: hamming
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int dist(int x, int y);

int main() {
	ifstream fin("hamming.in");
	ofstream fout("hamming.out");

	int n, b, d; fin >> n >> b >> d;
	int max = 1 << b;
	vector<int> nums;
	nums.push_back(0);

	for (int i = 1; i < max; i++) {
		if (dist(0, i) >= d) {
			nums.push_back(i);
		}
	}

	vector<bool> works(nums.size(), true);

	for (int i = 1; i < nums.size() - 1; i++) {
		if (!works[i]) {
			continue;
		}

		for (int j = i + 1; j < nums.size(); j++) {
			if (dist(nums[i], nums[j]) < d) {
				works[j] = false;
			}
		}
	}

	int printed = 0;

	for (int i = 0; i < nums.size(); i++) {
		if (printed == n) {
			break;
		}

		if (works[i]) {
			fout << nums[i];
			printed++;
			if (printed % 10 == 0) {
				fout << "\n";
			} else if (printed == n) {
				fout << "\n";
				break;
			} else {
				fout << " ";
			}
		}
	}

	return 0;
}

int dist(int x, int y) {
	int calc = x ^ y;
	int count = 0;

	while (calc > 0) {
		if (calc % 2 == 1) {
			count++;
		}

		calc /= 2;
	}

	return count;
}
