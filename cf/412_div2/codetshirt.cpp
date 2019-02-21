#include <iostream>
#include <vector>
#include <cmath>

#define vi vector<int>

using namespace std;

int main() {
	int n; cin >> n;
	int m = 0;
	int m2 = 0;
	vi s1(4, 0);
	vi l1(4, 0);
	vi s2(4, 0);
	vi l2(4, 0);

	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (s[0] == 'M') {
			m++;
		} else if (s[s.size() - 1] == 'S') {
			s1[s.size() - 1]++;
		} else {
			l1[s.size() - 1]++;
		}
	}

	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (s[0] == 'M') {
			m2++;
		} else if (s[s.size() - 1] == 'S') {
			s2[s.size() - 1]++;
		} else {
			l2[s.size() - 1]++;
		}
	}

	for (int i = 0; i < 4; i++) {
		int minx = min(s1[i], s2[i]);
		s1[i] -= minx;
		s2[i] -= minx;
	}

	for (int i = 0; i < 4; i++) {
		int minx = min(l1[i], l2[i]);
		l1[i] -= minx;
		l2[i] -= minx;
	}

	int ans = 0;

	for (int i = 0; i < 4; i++) {
		ans += s1[i];
		ans += s2[i];
		ans += l1[i];
		ans += l2[i];
	}

	ans += abs(m - m2);

	ans /= 2;

	cout << ans << '\n';

	return 0;
}
