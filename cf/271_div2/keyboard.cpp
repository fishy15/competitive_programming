#include <iostream>
#include <string>

using namespace std;

string top = "qwertyuiop";
string mid = "asdfghjkl;";
string bot = "zxcvbnm,./";

int inTop(char c);
int inMid(char c);
int inBot(char c);

int main() {
	char dir; cin >> dir; 
    string s; cin >> s;
    string ans; 
    
    for (int i = 0; i < s.size(); i++) {
        int t = inTop(s[i]);
        int m = inMid(s[i]);
        int b = inBot(s[i]);
        
        //cout << t << m << b << endl;
        if (dir == 'R') {
			if (t != -1) {
				ans += top[t - 1];
			} else if (m != -1) {
				ans += mid[m - 1];
			} else if (b != -1) {
				ans += bot[b - 1];
			}
		} else {
			if (t != -1) {
				ans += top[t + 1];
			} else if (m != -1) {
				ans += mid[m + 1];
			} else if (b != -1) {
				ans += bot[b + 1];
			}
		}
    }
    
    cout << ans << endl;
}

int inTop (char c) {
    for (int i = 0; i < 10; i++) {
		if (c == top[i]) {
			return i;
		}
	}
	
	return -1;
}

int inMid (char c) {
    for (int i = 0; i < 10; i++) {
		if (c == mid[i]) {
			return i;
		}
	}
	
	return -1;
}

int inBot (char c) {
    for (int i = 0; i < 10; i++) {
		if (c == bot[i]) {
			return i;
		}
	}
	
	return -1;
}

