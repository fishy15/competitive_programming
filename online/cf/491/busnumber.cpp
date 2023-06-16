#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef long long ll;

ll count;

ll fact(int n) {
	if (n == 0 || n == 1) {
		return 1;
	} 

	return n * (fact(n-1));
}

void doIt(vector<int> dig, int n, int loc) {
	/*
	for (int i = 0; i < 10; i++) {
		cout << dig[i] << " ";
	}
	cout << endl;
	*/
	//cout << ":::::\n";
	ll ans = fact(n);
	//cout << ans << endl;
	for (int i = 0; i < 10; i++) {
		ans /= fact(dig[i]);
	}
	//cout << ans << endl;

	if (dig[0] > 0) {
		ans *= n - dig[0];
		ans /= n;
	}

	//cout << loc << endl;
	//cout << ans << endl;

	::count += ans;

	for (int i = loc; i < 10; i++) {
		if (dig[i] > 1) {
			dig[i]--;
			doIt(dig, n - 1, i);
			dig[i]++;
		}
	}
}

int main() {
	ll n; cin >> n;
	string rep = to_string(n);
	vector<int> dig(10);
	for (int i = 0; i < rep.size(); i++) {
		//cout << rep[i] - '0' << endl;
		dig[rep[i] - '0']++;
	}

	doIt(dig, rep.size(), 0);

	cout << ::count << "\n";

	return 0;
}


