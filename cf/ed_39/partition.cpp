#include <iostream>
#include <math.h>
using namespace std;

int main() {
	int n; cin >> n;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int k; cin >> k;
		sum += abs(k);
	}

	cout << sum  << endl;
	return 0;
}
