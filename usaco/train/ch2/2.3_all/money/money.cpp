/*
ID: aaryan.1
TASK: money
LANG: C++11
*/

#include <iostream>
#include <fstream>

#define vi vector<int>
#define ll long long

using namespace std;

ll money[10001];

int main() {
	ifstream fin("money.in");
	ofstream fout("money.out");

	ll V, N; fin >> V >> N;
	money[0] = 1;

	for (int i = 0; i < V; i++) {
		int c; fin >> c;
		for (int j = 0; j <= N - c; j++) {
			money[j + c] += money[j];
			//cout << j + c << ' ' << money[j + c] << '\n';
		}
	}

	fout << money[N] << '\n';

	return 0;
}
