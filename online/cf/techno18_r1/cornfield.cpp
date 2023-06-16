#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

// 0 if on line
// 1 if above line
// -1 if below line
int posToLine(int x, int y, int m, int b);

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n, d; cin >> n >> d;
	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int x, y; cin >> x >> y;
		int pos1, pos2, pos3, pos4;
		pos1 = posToLine(x, y, 1, -d);
		pos2 = posToLine(x, y, 1, d);
		pos3 = posToLine(x, y, -1, d);
		pos4 = posToLine(x, y, -1, 2 * n - d);

		//printf("%d %d %d %d\n", pos1, pos2, pos3, pos4);
		if (pos1 == -1 || pos2 == 1 || pos3 == -1 || pos4 == 1) {
			cout << "NO\n";
		} else {
			cout << "YES\n";
		}
	}

	return 0;
}

int posToLine(int x, int y, int m, int b) {
	int val = x * m + b;
	if (val == y) {
		return 0;
	} else if (val > y) {
		return -1;
	} 

	return 1;
}