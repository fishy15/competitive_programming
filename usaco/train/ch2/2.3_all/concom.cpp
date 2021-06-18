/*
ID: aaryan.1
TASK: concom
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

struct node {
	bool solved;
	bool queue;
	int index;
	vector<int> owns;

	node(int i) {
		index = i;
		solved = false;
		queue = false;
		owns = vector<int>(101, 0);
	}
};

int N;
vector<node> comp;
vector<pair<int, int> > ans;

void solve(int index);

int main() {
	ifstream fin("concom.in");
	ofstream fout("concom.out");

	for (int i = 0; i <= 100; i++) {
		comp.push_back(node(i));
	}

	fin >> N;

	for (int i = 0; i < N; i++) {
		int a, b, c; fin >> a >> b >> c;
		comp[a].owns[b] = c;
	}

	for (int i = 1; i <= 100; i++) {
		solve(i);
	}
	
	sort(ans.begin(), ans.end());

	for (int i = 0; i < ans.size(); i++) {
		if (ans[i].first != ans[i].second) {
			fout << ans[i].first << ' ' << ans[i].second << '\n';
		}
	}

	return 0;
}

void solve(int i) {
	if (comp[i].solved) {
		return;
	}

	comp[i].queue = true;

	//cout << i << endl;

	int added = 0;

	do {
		added = 0;

		for (int j = 1; j <= 100; j++) {
			//cout << "J " << j << endl;
			if (comp[i].owns[j] > 50 && comp[i].owns[j] <= 100) {
				if (i == j) {
					continue;
				}

				if (!comp[j].solved && !comp[j].queue) {
					solve(j);
				}

				added++;
				//cout << "adding " << j << " to " << i << endl;
				comp[i].owns[j] = 101;

				for (int k = 1; k <= 100; k++) {
					if (comp[j].owns[k] == 101) {
						comp[i].owns[k] = 101;
					} else {
						comp[i].owns[k] += comp[j].owns[k];
						comp[i].owns[k] = comp[i].owns[k] > 100 ? 101 : comp[i].owns[k];
					}
				}
			}
		}

		/*
		for (int u : comp[i].owns) {
			cout << u << ' ';
		} cout << endl;
		cout << added << endl;
		*/

	} while (added > 0);

	for (int j = 1; j <= 100; j++) {
		if (comp[i].owns[j] == 101) {
			//cout << i << " owns " << j << endl;
			ans.push_back(make_pair(i, j));
		}
	}

	comp[i].solved = true;
	comp[i].queue = false;
}
