#include <iostream>
#include <string>

using namespace std; 

struct vowels {
	char vow[12] =  {'a', 'e', 'i', 'o', 'u', 'y',
			  'A', 'E', 'I', 'O', 'U', 'Y'};
			  
	bool isVowel(char c) {
		for (int i = 0; i < 12; i++) {
			if (c == vow[i]) {
				return true;
			}
		}
		
		return false;
	}
};

int main() {
	vowels vow;
	string s; cin >> s;
	string ans;
	
	for (int i = 0; i < s.size(); i++) {
		if (vow.isVowel(s[i])) {
			continue;
		}
		
		ans += '.';
		if (s[i] > 'Z') {
			ans += s[i];
		} else {
			ans += s[i] - 'A' + 'a';
		}
	}
	
	cout << ans << endl;
}
