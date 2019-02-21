/*
ID: aaryan.1
TASK: zerosum
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int N;
ofstream fout("zerosum.out");

void dfs(string prev, int num);
bool calc(string s);

int main() {
	ifstream fin("zerosum.in");

	fin >> N;
	dfs("1", 1);

	return 0;
}

void dfs(string prev, int num) {
	//cout << prev << endl;
	if (num == N) {
		if (calc(prev)) {
			fout << prev << '\n';
		}
	} else {
		prev += ' ';
		prev += to_string(num + 1);
		dfs(prev, num + 1);
		prev[prev.size() - 2] = '+';
		dfs(prev, num + 1);
		prev[prev.size() - 2] = '-';
		dfs(prev, num + 1);
	}
}

bool calc(string s) {
	vector<int> nums;
	vector<char> ops;
	int curNum = 0;
	for (int i = 0; i < s.size(); i++) {
		if (i == s.size() - 1) {
			curNum += s[i] - '0';
			nums.push_back(curNum);
		} else if (s[i] == ' ') {
			curNum *= 10;
		} else if (s[i] == '+' || s[i] == '-') {
			nums.push_back(curNum);
			curNum = 0;
			ops.push_back(s[i]);
		} else {
			curNum += s[i] - '0';
		}
	}

	int total = nums[0];
	//cout << total << ' ';
	for (int i = 0; i < ops.size(); i++) {
		//cout << ops[i] << ' ' << nums[i + 1] << ' ';
		if (ops[i] == '+') {
			total += nums[i + 1];
		} else {
			total -= nums[i + 1];
		}
	}
	//cout << '\n';

	//cout << total << endl;

	if (total == 0) {
		return true;
	}

	return false;
}

