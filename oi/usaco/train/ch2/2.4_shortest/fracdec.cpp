/*
ID: aaryan.1
TASK: fracdec
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

int main() {
	ifstream fin("fracdec.in");
	ofstream fout("fracdec.out");

	int p, q; fin >> p >> q;

	int whole = p / q;
	p %= q;
	//cout << p << endl;

	int repPos = -1;
	vector<int> prevNum;
	map<int, int> loc;
	int index = 0;

	while (p > 0) {
		//cout << p << endl;
		int next = 10 * p;
		p = next % q;
		//cout << next / q << endl;
		if (loc.find(p) != loc.end()) {
			repPos = loc.find(p)->second;
			if (prevNum[repPos] != (next / q)) {
				prevNum.push_back(next / q);
				repPos++;
			}
			break;
		}

		prevNum.push_back(next / q);
		loc.insert(make_pair(p, index));
		index++;
	}

	//cout << repPos << endl;
	string ans = "";

	/*
	for (int i : prevP) {
		cout << i << endl;
	}
	*/

	ans += to_string(whole) + '.';
	for (int i = 0; i < prevNum.size(); i++) {
		if (repPos == i) {
			ans += '(';
		}

		ans += prevNum[i] + '0';
	}

	if (repPos > -1) {
		//cout << "HI\n";
		ans += ')';
	}

	if (prevNum.empty()) {
		ans += '0';
	}

	for (int i = 0; i < ans.size(); i++) {
		if (i % 76 == 0 && i > 0) {
			fout << '\n';
		} 

		fout << ans[i];
	}

	fout << '\n';
	return 0;
}
