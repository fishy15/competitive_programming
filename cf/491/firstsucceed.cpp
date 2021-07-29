#include <iostream>

using namespace std;

int main() {
	int A, B, C, N; cin >> A >> B >> C >> N;
	int ans = N - A - B + C;
	if (ans < 1 || N <= A || N <= B || N <= C || C > A || C > B) {
		cout << "-1\n";
	} else {
		cout << ans << "\n";
	}

	return 0;
}
