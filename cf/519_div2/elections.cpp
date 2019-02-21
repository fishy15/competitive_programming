#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int max(int, int);
int main() {
	int n; cin >> n;
	int sum = 0;
    int maxval = 0;
	
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		sum += x;
        maxval = x > maxval ? x : maxval;
	}

    int res1 = 2 * sum / n + 1;
	cout << max(res1, maxval) << '\n';
	return 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}
