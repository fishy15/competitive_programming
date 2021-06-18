/*
ID: aaryan.1
TASK: lamps
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#define vi vector<int>
#define ull unsigned long long

using namespace std;

int N, C;
set<vi> ans;
vi r;
ofstream fout("lamps.out");

bool check(vi &cur);
void dfs(vi cur, int lev);
ull conv(vi num);
void printNum(ull num);
void printVi(vi v);

int main() {
	ifstream fin("lamps.in");

	fin >> N;
	fin >> C;

	C = C > 4 ? 4 : C;

	r = vi(N + 1, 0);

	int x = -1;

	do {
		fin >> x;
		if (x > -1) {
			r[x - 1] = 1;
		} 
	} while (x > -1);

	do {
		fin >> x;
		if (x > -1) {
			r[x - 1] = -1;
		} 
	} while (x > -1);

	vi temp(N, 1);
	dfs(temp, 0);

	if (ans.empty()) {
		fout << "IMPOSSIBLE\n";
	} else {
		for (vi i : ans) {
			printVi(i);
		}
	}

	return 0;
}

bool check(vi &cur) {
	for (int i = 0; i < N; i++) {
		if (r[i] + cur[i] == 0) {
			return false;
		}
	}

	return true;
}

ull conv(vi num) {
	ull ans = 0;
	for (int i = 0; i < N; i++) {
		if (num[i] == 1) {
			ans++;
		}

		ans = ans << 1;
	}

	return ans >> 1;
}

void dfs(vi cur, int lev) {
	//printNum(conv(cur));
	if (lev == C) {
		/*
		for (int i : cur) {
			cout << i << " ";
		}

		cout << endl;
		*/
		if (check(cur)) {
			ans.insert(cur);
		}
	} else {
		vi copy = vi(cur);
		vi copy2 = vi(cur);
		vi copy3 = vi(cur);
		vi copy4 = vi(cur);

		for (int i = 0; i < N; i++) {
			copy[i] = -copy[i];
			if (i % 2 == 0) {
				copy2[i] = -copy2[i];
			} else {
				copy3[i] = -copy3[i];
			}

			if (i % 3 == 0) {
				copy4[i] = -copy4[i];
			}
		}

		dfs(copy, lev + 1);
		dfs(copy2, lev + 1);
		dfs(copy3, lev + 1);
		dfs(copy4, lev + 1);
	}
}

void printNum(ull num) {
	cout << num << endl;
	for (int i = N - 1; i >= 0; i--) {
		fout << ((num >> i) % 2);
	}

	fout << '\n';
}

void printVi(vi v) {
	for (int i = 0; i < N; i++) {
		if (v[i] == 1) {
			fout << 1;
		} else {
			fout << 0;
		}
	}

	fout << '\n';
}
