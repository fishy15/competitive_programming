/*
ID: aaryan.1
TASK: runround
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

typedef unsigned long long ull;

bool works(ull n) {
	//cout << n << endl;
	string num = to_string(n);
	int len = num.size();
	int index = 0;
	int count = 0;

	set<char> t;

	while (num[index] != '0') {
		if (t.find(num[index]) != t.end()) {
			break;
		}

		t.insert(num[index]);
		//cout << num << endl;
		//cout << num[index] << endl;
		int newIndex = (num[index] - '0' + index) % len;
		num[index] = '0';
		count++;
		index = newIndex;
		//cout << "I " << index << endl;
		//cout << "is " << num[index] << endl;
	}
    
	return (count == len && index == 0);
}

int main() {
	ifstream fin("runround.in");
	ofstream fout("runround.out");

	ull n; fin >> n;

	n++;

	while(!works(n)) {
		n++;
	}

	fout << n << '\n';

	return 0;
}
