/*
ID: aaryan.1
TASK: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#define vi vector<int>
#define vii vector<vi>

using namespace std;


int V;
int G;
bool foundIt;
vi vitamins;
vii feeds(1);
ofstream fout("holstein.out");

void bfs(vii &sums, vii &picked);
bool check(vi &sum);

int main() {
	ifstream fin("holstein.in");

	fin >> V;
	for (int i = 0; i < V; i++) {
		int x; fin >> x;
		vitamins.push_back(x);
	}

	fin >> G;
	for (int i = 1; i <= G; i++) {
		vi feed;
		for (int j = 0; j < V; j++) {
			int x; fin >> x;
			feed.push_back(x);
			//cout << x << endl;
		}

		feeds.push_back(feed);
		//cout << "feeds is " << feeds.size() << endl;
	}
	/*
	cout << V << ' ' << G << endl;

	for (int i = 1; i < feeds.size(); i++) {
		cout << "HI\n";
		for (int j = 0; j < V; j++) {
			cout << i << ' ' << j << ' ' << feeds[i][j] << endl;
		}
	}
	*/

	vii temp1 = vii(0);
	vii temp2 = vii(0);

	bfs(temp1, temp2);	

	return 0;
}

bool check(vi &sum) {
	for (int i = 0; i < V; i++) {
		if (sum[i] < vitamins[i]) {
			return false;
		}
	}

	return true;
}

void bfs(vii &sums, vii &picked) {
	//cout << "level\n";
	vii nextSum;
	vii nextPick;

	if (picked.size() == 0) {
		for (int i = 1; i <= G; i++) {
			vi choice(feeds[i]);
			vi p = vi(1, i);

			nextSum.push_back(choice);
			nextPick.push_back(p);
			//cout << "size\n";
			//cout << nextPick.size() << endl;
		}
	} else {
		for (int i = 0; i < picked.size(); i++) {
			/*
			cout << "i is " << i << endl;
			cout << "last is " << picked[i].size() - 1 << endl;
			for (int i : picked[i]) {
				cout << i << " ";
			}
			cout << "fatty\n";
			cout << "which is " << picked[i][picked[i].size() - 1] << endl;
			*/
			for (int j = picked[i][picked[i].size() - 1] + 1; j <= G; j++) {
				//cout << "j is " << j << endl;
				//cout << "HI\n";
				vi copySum(sums[i]);
				vi copyPick(picked[i]);
				//cout << "copied\n";

				for (int k = 0; k < V; k++) {
					/*
					cout << k << endl;
					cout << "copylen is " << copySum.size() << endl;
					cout << "feedslen is " << feeds[j].size() << endl;
					cout << j << " " << k << endl;
					*/
					copySum[k] += feeds[j][k];
				}

				copyPick.push_back(j);

				nextSum.push_back(copySum);
				nextPick.push_back(copyPick);
			}
		}
	}

	// printing
	/*
	for (int i = 0; i < nextPick.size(); i++) {
		for (int j = 0; j < nextPick[0].size(); j++) {
			cout << nextPick[i][j] << " ";
		}

		cout << endl;
	}
	*/

	for (int i = 0; i < nextSum.size(); i++) {
		if (check(nextSum[i])) {
			fout << nextPick[i].size();

			for (int j = 0; j < nextPick[i].size(); j++) {
				fout << " " << nextPick[i][j];
			}

			fout << "\n";
			foundIt = true;
			break;
		}
	}

	if (!foundIt) {
		bfs(nextSum, nextPick);
	}
}

