#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<int> mov;
	
	for (int i = 0; i < n - 1; i++) {
		int x; cin >> x;
		mov.push_back(x);
	}

	int loc = 0;
	bool ans = false;
	while (loc < n - 1) {
		//cout << loc << endl;
		if (loc == m - 1) {
			ans = true;
			break;
		}

		loc += mov[loc];
	}

	if (ans || loc == m - 1) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}

	return 0;
}
