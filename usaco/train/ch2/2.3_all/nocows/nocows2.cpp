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

	//cout << "HI\n";
	if (N % 2 == 0) {
		//cout << "is it here\n";
		fout << "0\n";
		//cout << "check\n";
	} else {
		//cout << "wut\n";
		branch = vvi(N + 1, vi(K + 1, 0));
		//cout << "HI\n";
		for (int i = 1; i <= K; i++) {
			branch[1][i] = 1;
		}

		for (int i = 1; i <= K; i++) {
			for (int j = 2; j <= N; j++) {
				for (int k = 1; k <= j - 2; k++) {
					//cout << i << ' ' << j << ' ' << k << endl;
					branch[j][i] += branch[k][i - 1] * branch[j - k - 1][i - 1];
					branch[j][i] %= MOD;
				}
			}
		}
	
		/*
		for (auto i : branch) {
			for (auto j : i) {
				cout << j << ' ';
			}
			cout << endl;
		}
		*/

		fout << (branch[N][K] - branch[N][K - 1] + 9901) % 9901 << '\n';
	}
	return 0;
}
