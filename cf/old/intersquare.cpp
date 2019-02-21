#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool intersect(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3, pair<int, int> p4) {
	bool ans1 = false;
	bool ans2 = false;
	if (max(p1.first, p1.first) >= min(p2.first, p2.first) && (max(p2.first, p2.first) >= min(p1.first, p1.first))) {
		ans1 = true;
	}

	if (max(p1.second, p1.second) >= min(p2.second, p2.second) && (max(p2.second, p2.second) >= min(p1.second, p1.second))) {
		ans2 = true;;
	}

	cout << ans1 << ans2 << endl;
	return ans1 && ans2;
}

int main() {
	vector<pair<int, int>> sq1;
	vector<pair<int, int>> sq2;

	for (int i = 0; i < 4; i++) {
		int x, y; cin >> x >> y;
		sq1.push_back(make_pair(x, y));
	}

	sort(sq1.begin(), sq1.end());

	for (int i = 0; i < 4; i++) {
		int x, y; cin >> x >> y;
		sq2.push_back(make_pair(x, y));
	}

	sort(sq2.begin(), sq2.end());

	// check if sq2 is inside sq1

	bool intersect = false;
	bool val = true;
	for (int i = 0; i < 4; i++) {
		if (sq2[i].first < sq1[0].first ||
		    sq2[i].first > sq1[2].first) {
			val = false;
			break;
		}

		if (sq2[i].second < sq1[0].second ||
		    sq2[i].second > sq1[1].second) {
			val = false;
			break;
		}
	}

	cout << val << endl;

	intersect = intersect || val;

	// check if sq1 is "in" sq2 (not really)
	val = true;
	for (int i = 0; i < 4; i++) {
		if (sq1[i].first < sq2[0].first ||
		    sq1[i].first > sq2[3].first) {
			val = false;
			break;
		}

		if (sq1[i].second < sq2[1].second ||
		    sq1[i].second > sq2[2].second) {
			val = false;
			break;
		}
	}

	cout << val << endl;

	intersect = intersect || val;

	val = false;

	int next[4] = {1, 3, 2, 0};
	// checks each pair of line segments
	for (int i = 0; i < 4 && !val; i++) {
		for (int j = 0; j < 4 && !val; j++) {
			if (::intersect(sq1[i], sq1[next[i]], sq2[j], sq2[next[j]])) {
				cout << "*" << i << j << endl;
				//cout << sq1[i].first << " " << sq1[o]
				val = true;
			}
		}
	}

	cout << val << endl;

	intersect = intersect || val;

	if (intersect) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}

	return 0;
}



	

	
