#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N; cin >> N;

	vector<int> a, b, c;
	for (int i = 0; i < N; i++) {
		int x, y, z; cin >> x >> y >> z;
		a.push_back(x);
		b.push_back(y);
		c.push_back(z);
	}

	for (
