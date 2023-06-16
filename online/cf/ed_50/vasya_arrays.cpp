#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	vector<long long> pre1, pre2;
	pre1.push_back(0);
	pre2.push_back(0);

	int n, m; cin >> n;
	for (int i = 0; i < n; i++) {
		long long x; cin >> x;
		pre1.push_back(x + pre1[i]);
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		long long x; cin >> x;
		pre2.push_back(x + pre2[i]);
	}
	
	if (pre1[n] != pre2[m]) {
		cout << "-1\n";
		return 0;
	}

	int last1 = 0;
	int last2 = 0;
	int cur1 = 1;
	int cur2 = 1;

	int count = 0;
	while (cur1 <= n && cur2 <= m) {
		long long total1 = pre1[cur1] - pre1[last1];
		long long total2 = pre2[cur2] - pre2[last2];
		
		if (total1 == total2) {
			/*
			cout << "total1: " << total1 << endl;
			cout << "total2: " << total2 << endl;
			cout << last1 << " to " << cur1 << '\n';
			cout << last2 << " to " << cur2 << "\n\n\n";
			*/
			count++;
			last1 = cur1;
			last2 = cur2;
			cur1++;
			cur2++;
		} else if (total1 < total2) {
			cur1++;
		} else {
			cur2++;
		}		
	}
	
	cout << count << '\n';
	
	return 0;
}
