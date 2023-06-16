/*
ID: aaryan.1
TASK: barn1
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");

	int m, s, c; fin >> m >> s >> c;
	vector<int> cows; 

	for (int i = 0; i < c; i++) {
		int x; fin >> x;
		cows.push_back(x);
	}

	sort(cows.begin(), cows.end());

	vector<int> gaps;

	for (int i = 1; i < c; i++) {
		gaps.push_back(cows[i] - cows[i - 1] - 1);
	}

	sort(gaps.begin(), gaps.end());

	int blocked = cows[c - 1] - cows[0] + 1;
	//cout << "B" << blocked << endl;
	int counter = gaps.size() - 1;

	// is done to m - 1 bc there are m - 1 gaps between m lines
	for (int i = 0; i < m - 1; i++) {
		if (counter < 0) {
			break;
		}
		//cout << counter << "?" << gaps.size() << endl;
		//cout << "!" << gaps[counter] << endl;
		blocked -= gaps[counter];
		counter--;
	}

	fout << blocked << endl;

	return 0;
}






