/*
ID: aaryan.1
TASK: prefix
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int maxVal;
int sz;
string s;
vector<string> p;
vector<bool> works;
set<int> start;

void bfs();

int main() {
	ifstream fin("prefix.in");
	ofstream fout("prefix.out");

	string x = "";
	while (x != "x") {
		fin >> x;

		if (x == ".") {
			x = "x";
			break;
		}

		p.push_back(x);
	}

	string temp;
	do {
		fin >> temp;
		s += temp;
		temp = "";
	} while (!fin.eof());

	sz = s.size();

	//cout << s << "\nend\n";

	works = vector<bool>(sz, false);
	works[0] = true;

	start.insert(0);
	bfs();

	fout << maxVal << '\n';

	return 0;
}

void bfs() {
	//cout << "hi hi hi <3\n";
	set<int> next;
	for (int i : start) {
		for (int j = 0; j < p.size(); j++) {
			//cout << "j " << p[j] << endl;
			//cout << s.substr(i, p[j].size()) << endl;
			if (works[i + p[j].size()]) {
				continue;
			}

			if (s.substr(i, p[j].size()) == p[j]) {
				//cout << s.substr(0, p[j].size() + i) << endl;
				next.insert(i + p[j].size());
				works[i + p[j].size()] = true;
				//cout << i + p[j].size() << endl;
				if (i + p[j].size() > maxVal) {
					maxVal = (i + p[j].size());
				}
			}
		}
	}

	if (!next.empty()) {
		start = next;
		bfs();
	}
}
