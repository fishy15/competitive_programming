/* 
ID: aaryan.1
TASK: palsquare
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool paliCheck(string &s1, string &s2) {
	if (s1.size() != s2.size()) {
		return false;
	}

	for (int i = 0; i < s1.size(); i++) {
		if (s1[i] != s2[s1.size() - i - 1]) {
			return false;
		}
	}

	return true;
}

string convBase(int val, int base) {
	string ans = "";
	int baseExp = base;
	string converter = "0123456789ABCDEFGHIJ";
	while (val > 0) {
		ans = converter[val % baseExp] + ans;
		val /= baseExp;
		//baseExp *= base;
	}
	//cout << ans << endl;
	return ans;
}

int main() {
	
	ifstream fin("palsquare.in");
	ofstream fout("palsquare.out");

	int n; fin >> n;

	for (int i = 1; i <= 300; i++) {
		int square = i*i;
		string conv = convBase(square, n);
		if (paliCheck(conv, conv)) {
			fout << convBase(i, n) << " " << conv << endl;
		}
	}

	return 0;
}

