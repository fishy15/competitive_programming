/*
ID: aaryan.1
TASK: namenum
LANG: C++
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string convNum(string name) {
	string ans = "";
	cout << name.size() << endl << name << endl;
	for (int i = 0; i < name.size(); i++) {
		cout << name.size() << endl << name[i] << endl;
		switch(name[i]) {
			case 'A': case 'B': case 'C': ans += "2"; break;
			case 'D': case 'E': case 'F': ans += "3"; break;
			case 'G': case 'H': case 'I': ans += "4"; break;
			case 'J': case 'K': case 'L': ans += "5"; break;
			case 'M': case 'N': case 'O': ans += "6"; break;
			case 'P': case 'R': case 'S': ans += "7"; break;
			case 'T': case 'U': case 'V': ans += "8"; break;
			case 'W': case 'X': case 'Y': ans += "9"; break;
		}
	}
	return ans;
}

int main() {
	ifstream fin("namenum.in");
	ifstream dict("dict.txt");
	ofstream fout("namenum.out");
	string num; fin >> num;
	bool works = false;
	for (int i = 0; i < 5000; i++) {
		string name; dict >> name;
		if (name.size() == num.size()) {
			string mnum = convNum(name);
			if (mnum == num) {
				works = true;
				fout << name << endl;
			}
		}
	}

	if (!works) {
		fout << "NONE\n";
	}

	return 0;
}
