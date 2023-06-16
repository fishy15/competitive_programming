#include <iostream>
#include <string>

using namespace std;

bool isVowel(char let) {
	return let == 'a' || let == 'e' || let == 'i' || let == 'o' || let == 'u';
}

bool isN(char c) {
	return c == 'n';
}

int main() {
	string s; cin >> s;
	bool check = false;
	for (int i = 0; i < s.size(); i++) {
		char let = s[i];
		if (isVowel(let) || isN(let)) {
			continue;
		} else {
			if (i == s.size() - 1 || !isVowel(s[i + 1])) {
				cout << "NO\n";
				return 0;
			}
		}
	}

	cout << "YES\n";
	return 0;
}
