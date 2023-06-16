/*
ID: aaryan.1
TASK: subset
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>

#define ll long long

using namespace std;

int main() {
	ifstream fin("subset.in");
	ofstream fout("subset.out");

	int N; fin >> N;

	int sum = N * (N + 1) / 2;

	if (sum % 2 == 1) {
		fout << "0\n";
	} else {
		vector<ll> v(sum + 1, 0);
		v[0] = 1;
		
		for (int i = 1; i<= N; i++) {
			for (int j = sum - 1; j >= 0; j--) {
				if (v[j] == 0) {
					continue;
				}

				v[j + i] += v[j];
			}

			/*
			for (int x : v) {
				cout << x << ' ';
			}

			cout << endl;
			*/
		}

		fout << v[sum / 2] / 2 << '\n';
	}

	return 0;
}
