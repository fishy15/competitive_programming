#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
	ifstream fin("msched.in");
	ofstream fout("msched.out");

	int N; fin >> N;
	vector<pair<int, int> > cows;

	for (int i = 0; i < N; i++) {
		int x, y; fin >> x >> y;
		cows.push_back(make_pair(x, y));
	}

	sort(cows.begin(), cows.end(), [](const pair<int, int> &p1, const pair<int, int> &p2) -> bool {
		if (p1.second == p2.second) {
			return p1.first > p2.first;
		}

		return p1.second < p2.second;
	});

	for (auto p : cows) {
		cout << p.first << ' ' << p.second << endl;
	}

	int ans = 0;
	int time = 1;
	for (int i = 0; i < N; i++) {
		if (cows[i].second >= time) {
			//cout << cows[i].first << endl;
			//cout << cows[i].second << ' ' << time << endl;
			ans += cows[i].first;
			time++;
		}
	}

	fout << ans << '\n';

	return 0;
}
