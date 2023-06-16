#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<string> strings;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		strings.push_back(s);
	}
	
	sort(strings.begin(), strings.end(), [](string s1, string s2) {
		return s1.size() < s2.size();
	});

	bool works = true;

	for (int i = 1; i < strings.size(); i++) {
		if (strings[i].find(strings[i - 1]) == string::npos) {
			works = false;
			break;
		}
	}

	if (works) {
		cout << "YES\n";
		for (int i = 0; i < strings.size(); i++) {
			cout << strings[i] << endl;
		}
	} else {
		cout << "NO\n";
	}

	return 0;
}
