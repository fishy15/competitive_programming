#include <iostream>
#include <queue>

using namespace std;

int total;
queue<int> deck1;
queue<int> deck2;

int war();

int main() {
	int n; cin >> n;
	int k1; cin >> k1;
	for (int i = 0; i < k1; i++) {
		int x; cin >> x;
		deck1.push(x);
	}

	int k2; cin >> k2;
	for (int i = 0; i < k2; i++) {
		int x; cin >> x;
		deck2.push(x);
	}

	int res = -1;
	for (int i = 0; i < 1000; i++) {
		res = war();
		if (res > -1) {
			break;
		}
	}

	if (res == -1) {
		cout << "-1\n";
	} else {
		cout << total << ' ' << res << '\n';
	}

	return 0;
}

int war() {
	int f = deck1.front();
	int s = deck2.front();

	//cout << f << ' ' << s << '\n';
	//cout << deck1.size() << endl;
	//cout << deck2.size() << endl;

	deck1.pop();
	deck2.pop();

	if (f > s) {
		deck1.push(s);
		deck1.push(f);
	} else {
		deck2.push(f);
		deck2.push(s);
	}

	total++;

	if (deck1.empty()) {
		//cout << "HI" << endl;
		return 2;
	} else if (deck2.empty()) {
		//cout << "BYE" << endl;
		return 1;
	}

	return -1;
}
