#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string first, second; cin >> first >> second;
	vector<int> diff;
	for (int i = 0; i < first.size(); i++) {
		if (first[i] != second[i]) {
			diff.push_back(i);
		}
	}

	if (diff.size() % 2 == 1) {
		cout << "impossible\n";
	} else {
		int counter = 0;
		string ans = "";
		for (int i = 0; i < first.size(); i++) {
			if (i == diff[counter]) {
				ans += (counter % 2) + '0';
				counter++;
			} else {
				ans += first[i];
			}
		}

		cout << ans << endl;
	}

	return 0;
}
