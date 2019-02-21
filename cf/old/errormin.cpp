#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, k1, k2; cin >> n >> k1 >> k2;
	int k = k1 + k2;
	
	vector<int> a, b;
	for (int i = 0; i < n; i++) {
		int an, bn; cin >> an >> bn;
		a.push_back(an);
		b.push_back(bn);
	}
	
	vector<int> e;
	for (int i = 0; i < n; i++) {
		e.push_back(abs(a[i] - b[i]));
	}
	
	sort(e.begin(), e.end());
	
	while (k > 0) {
		sort(e.begin(), e.end());
		//if (e[n - 1] == 0) break;
		e[n - 1]--;
		//cout << e[n - 1] << endl;
		k--;
	}
	
	int error;
	for (int i = 0; i < n; i++) {
		error += e[i] * e[i];
	}
	
	cout << error << endl;
}
