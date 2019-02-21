/* 
ID: aaryan.1
TASK: combo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
	ifstream fin("combo.in");
	ofstream fout("combo.out");

	int n; fin >> n;

	int first[3];
	for (int i = 0; i < 3; i++) {
		int x; fin >> x;
		first[i] = x;
	}

	int second[3];
	for (int i = 0; i < 3; i++) {
		int x; fin >> x;
		second[i] = x;
	}

	int total = min(250, n*n*n); 

	int diff[3];
	for (int i = 0; i < 3; i++) {
		diff[i] = abs(first[i] - second[i]);
		//cout << "!" << diff[i] << endl;
		diff[i] = min(diff[i], n - diff[i]);
		//cout << diff[i] << " " << n - diff[i] << endl;
	}

	int prod = 1;
	for (int i = 0; i < 3; i++) {
		//cout << max(5 - diff[i], 0) << endl;
		prod *= max(5 - diff[i], 0);
	}

	if (total - prod <= 0) {
		fout << total << "\n";
	} else {
		fout << total - prod << endl;
	}

	return 0;
}
	
