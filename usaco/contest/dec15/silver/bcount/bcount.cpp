#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
	ifstream fin("bcount.in");
	ofstream fout("bcount.out");

	int n, q; fin >> n >> q;
	vector<vector<int> > b;
	vector<int> count = {0, 0, 0};

	for (int i = 0; i < n; i++) {
		b.push_back(count);
		int x; fin >> x;
		count[x - 1]++;
	}

	b.push_back(count);

	/*
	0 0 0
	0 1 0
	1 1 0
	2 1 0
	2 1 1 
	2 2 1 
	3 2 1
	*/

	for (int i = 0; i < q; i++) {
		int l, r; fin >> l >> r;
		for (int j = 0; j < 3; j++) {
			//cout << b[r][j] << ' ' << b[l - 1][j] << endl;
			fout << b[r][j] - b[l - 1][j];
			if (j == 2) {
				fout << '\n';
			} else {
				fout << ' ';
			}
		}
	}

	return 0;
}

