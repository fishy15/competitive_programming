/*
ID: aaryan.1
TASK: nocows
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#define ll long long
#define vi vector<int>
#define vvi vector<vi>
#define MOD 9901

using namespace std;

int N, K;
vvi branch;

int calc(int n, int k);

int main() {
	ifstream fin("nocows.in");
	ofstream fout("nocows.out");

	fin >> N >> K;

	if (N % 2 == 0) {
		fout << "0\n";
	} else {
		branch = vvi(N + 1, vi(K + 1, -1));
		calc(N, K);
		fout << (branch[N][K] + 9901) % 9901 << '\n';
	}

	///*
	for (auto i : branch) {
		for (auto j : i) {
			cout << j << ' ';
		}
		cout << endl;
	}
	//*/

	return 0;
}

int calc(int n, int k) {
	//cout << n << ' ' << k << endl;
	if (branch[n][k] > -1) {
		// moved statement to the end of method
		//cout << "already " << n << ' ' << k << endl;
	} else if (k == 0) {
		//cout << "k is 0\n";
		branch[n][k] = 0;
	} else if (n == 1) {
		//cout << "n is 1\n";
		branch[n][k] = 1;
	} else {
		branch[n][k] = 0;
		for (int i = 1; i <= n-2; i += 2) {
			branch[n][k] += calc(i, k - 1) * calc(n - i - 1, k - 1);
			branch[n][k] = branch[n][k] % 9901;
			//cout << "vals: ";
			//cout << branch[i][k - 1] << ' ' << branch[n - i - 1][k - 1] << endl;
			//cout << '\t' << n << ' ' << k << ' ' << branch[n][k] << endl;
		}

		//cout << n << ' ' << k << ' ' << branch[n][k] << endl;
	}

	return branch[n][k];
}
