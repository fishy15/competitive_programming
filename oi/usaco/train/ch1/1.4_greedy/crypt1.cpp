/*
ID: aaryan.1
TASK: crypt1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkIn(int num, vector<int> &checker);

int main() {
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");

	int n; fin >> n;

	vector<int> dig;

	for (int i = 0; i < n; i++) {
		int x; fin >> x;
		dig.push_back(x);
	}

	sort(dig.begin(), dig.end());

	int count = 0;

	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			for (int c = 0; c < n; c++) {
				for (int d = 0; d < n; d++) {
					for (int e = 0; e < n; e++) {
						int x = 100*dig[a]+10*dig[b]+dig[c];
						//cout << "X" <<  x << endl;
						//cout << "d" << dig[d] << "e" << dig[e] << endl;
						int p1 = x*dig[d];
						int p2 = x*dig[e];
						//cout << p2 << p1 << endl;
						if (p1 < 100 || p1 > 999) {
							continue;
						}

						if (p2 < 100 || p2 > 999) {
							continue;
						}

						if (!checkIn(p1, dig)) {
							continue;
						}

						if (!checkIn(p2, dig)) {
							continue;
						}

						if (!checkIn((p1 + 10*p2)/10, dig)) {
							continue;
						}

						count++;

						//cout << "x" << x << endl;
						//cout << "d" << dig[d] << "e" << dig[e] << endl;
					}
				}
			}
		}
	}

	fout << count << endl;

	return 0;
}

bool checkIn(int num, vector<int> &checker) {
	bool f = binary_search(checker.begin(), checker.end(), num % 10);
	bool s = binary_search(checker.begin(), checker.end(), (num / 10) % 10);
	
	bool t = binary_search(checker.begin(), checker.end(), num / 100);

	return f && s && t;
}
