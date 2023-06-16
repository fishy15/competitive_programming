#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, m; cin >> n >> m;
	vector<int> drives;
	for (int i = 0; i < n; i++) {
		int s; cin >> s;
		drives.push_back(s);
	}

	sort(drives.begin(), drives.end());
	int sum = 0; 
	int i = 0; 
	while (sum < m) {
		sum += drives[n - i - 1];
		i++;
	}

	cout << i << endl;
	return 0;
}
