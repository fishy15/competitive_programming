#include <iostream>

using namespace std;

int main() {
	int ans[6][3] = {{0, 1, 2}, {1, 0, 2}, {1, 2, 0}, {2, 1, 0}, {2, 0, 1}, {0, 2, 1}};
	int n, x; cin >> n >> x;
	n = n % 6;	
	cout << ans[n][x] << endl;
	return 0;
}

/* Pattern:
 * 0 1 2 gen 0
 * 1 0 2 gen 1
 * 1 2 0 gen 2
 * 2 1 0 gen 3
 * 2 0 1 gen 4
 * 0 2 1 gen 5
 * 0 1 2 gen 6
*/
