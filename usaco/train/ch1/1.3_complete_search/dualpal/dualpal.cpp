/*
ID: aaryan.1
TASK: dualpal
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

	while (val > 0) {
		ans = to_string(val % baseExp) + ans;
		val /= baseExp;
		//baseExp *= base;
	}
	//cout << ans << endl;
	return ans;
}

int main() {
	ifstream fin ("dualpal.in");
	ofstream fout ("dualpal.out");
	
	int n, s; fin >> s >> n; 
	
	//cout << "---------\n";
	

	while (s > 0) {
		n++;
		int count = 0;
		//cout << "!" << n << endl;
		for (int i = 2; i <= 10; i++) {
			string conv = convBase(n, i);
			if (paliCheck(conv, conv)) {
				count++;
			}

			if (count == 2) {
				break;
			}
		}

		if (count == 2) {
			fout << n << endl;
			s--;
		}
	} 

	return 0;
}
