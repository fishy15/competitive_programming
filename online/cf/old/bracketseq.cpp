#include <iostream>
#include <string> 
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	int n; cin >> n;
	ll zero = 0;
	vector<int> other; 

	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		int c = 0;
		bool zeroWorks = true;
		bool worksAtAll = true;

		if (s.size() > 1) {
			if (s[0] == ')' && s[s.size() - 1] == '(') {
				worksAtAll = false;
			}
		}

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '(') {
				c++;
			} else if (s[i] == ')') {
				c--;
			}

			if (c < 0) {
				zeroWorks = false;
			}
		}

		if (c == 0) {
			if (zeroWorks) {
				zero++;
			}
			continue;
		}
		
		//cout << "! " << s << endl;
		if (worksAtAll) {
			other.push_back(c);
		}
	}

	ll ans = 0;

	for (int i = 0; i < other.size(); i++) {
		for (int j = i; j < other.size(); j++) {
			if (other[i] + other[j] == 0) {
				ans++;
				//cout << i << " " << j << "" << endl;
			}
		}
	}

	//cout << ans << endl;
	
	ans += zero * zero;

	cout << ans << endl;

	return 0;
}
