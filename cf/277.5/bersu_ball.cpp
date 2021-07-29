#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int abs(int x) {
	if (x < 0) return -x;
	return x;
}

int main() {
	int n; cin >> n;
	vector<int> boys(n);
	
	for (int i = 0; i < n; i++) {
		cin >> boys[i];
	}
	
	int m; cin >> m;
	vector<int> girls(m);
	for (int i = 0; i < m; i++) {
		cin >> girls[i];
	}
	
	sort(boys.begin(), boys.end());
	sort(girls.begin(), girls.end());
	
	int boyPos = 0;
	int girlPos = 0;
	int count = 0;
	
	while (boyPos < n && girlPos < m) {
		if (abs(boys[boyPos] - girls[girlPos]) <= 1) {
			//cout << "match " << boys[boyPos] << ' ' << girls[girlPos] << endl;
			count++;
			boyPos++;
			girlPos++;
		} else if (boys[boyPos] < girls[girlPos]) {
			boyPos++;
		} else {
			girlPos++;
		}
	}
	
	cout << count << '\n';
	return 0;
}