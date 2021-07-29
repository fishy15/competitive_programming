#include <iostream>
#include <string>
#include <vector> 

using namespace std;

int main() {
	int n; cin >> n; 
	bool works = false;
	vector<string> rows; 
	
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		if (!works) {
			if (s[0] == 'O' && s[1] == 'O') {
				works = true;
				s[0] = '+';
				s[1] = '+';
			} else if (s[3] == 'O' && s[4] == 'O') {
				works = true;
				s[3] = '+';
				s[4] = '+';
			}
		}
		
		rows.push_back(s); 
	}
	
	if (!works) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
	
		for (int i = 0; i < n; i++) {
			cout << rows[i] << endl;
		}
	}
	return 0;
}
