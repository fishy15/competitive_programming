#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define P 31
#define MOD (int)(10e9 + 9)

using namespace std;

string conv(vector<string> s);

int main() {
	ifstream fin("records.in");
	ofstream fout("records.out");

	int N; fin >> N;
	vector<string> nums;

	for (int i = 0; i < N; i++) {
		vector<string> s(3);
		
		for (int j = 0; j < 3; j++) {
			fin >> s[j];
		}

		nums.push_back(conv(s));
	}

	sort(nums.begin(), nums.end());

	//for (auto s : nums) {
		//cout << s << endl;
	//}

	int count = 1;
	int max = 0;
	for (int i = 1; i < N; i++) {
		//cout << nums[i] << endl;
		if (nums[i] == nums[i - 1]) {
			count++;
		} else {
			max = count > max ? count : max;
			count = 1;
		}
	}

	max = count > max ? count : max;

	fout << max << '\n';

	return 0;
}

string conv(vector<string> s) {
	string mega = "";

	sort(s.begin(), s.end());

	for (int i = 0; i < 3; i++) {
		mega += s[i];
		//cout << s[i] << ' ';
	}

	//cout << '\n';

	/*
	int hash = 0;
	
	for (int i = 0; i < mega.size(); i++) {
		hash = hash * P + mega[i];
		hash = (hash + MOD) % MOD;
	}
	*/

	//cout << mega << endl;
	return mega;
}
