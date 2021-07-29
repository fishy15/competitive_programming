#include <iostream>

using namespace std;

int main() {
	long long k; cin >> k;
	long long n; cin >> n;

	bool ans = false;
	int count = 0;
	long long num = k;
	while (num <= n) {
		if (num == n) {
			ans = true;
			break;
		} 

		num *= k;
		count++;
	}

	if (ans) {
		cout << "YES\n" << count << endl;
	} else {
		cout << "NO\n";
	}

	return 0;
}

