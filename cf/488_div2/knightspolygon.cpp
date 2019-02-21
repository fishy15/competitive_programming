#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	int n, k; cin >> n >> k;

	vector<int> power;
	vector<int> coins;

	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		power.push_back(x);
	}

	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		coins.push_back(x);
	}

	// first is coin, second is power
	vector<pair<int, int>> knights;

	for (int i = 0; i < n; i++) {
		knights.push_back(make_pair(coins[i], power[i]));
	}

	sort(knights.begin(), knights.end());

	/*
	for (pair<int, int> p : knights) {
		cout << p.first << ":" << p.second << endl;
	}
	*/

	vector<ll> ans;

	for (int i = 0; i < n; i++) {
		ll money = (ll)coins[i];
		int index = n - 1;
		int kill = k;
		while (kill > 0 && index >= 0) {
			if (knights[index].second < power[i]) {
				//cout << i << " kills " << index << endl;
				//cout << "gets " << knights[index].first << endl;
				money += (ll)knights[index].first;
				kill--;
			}

			index--;
		}

		ans.push_back(money);
	}

	for (ll i : ans) {
		cout << i << " ";
	}

	cout << "\n";
}


			


