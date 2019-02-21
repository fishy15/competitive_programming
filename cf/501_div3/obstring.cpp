#include <iostream>
#include <vector>
#include <string>

using namespace std;

int alpha[26];

int main() {
    cin.tie(0); sync_with_stdio(0);

    string s, t; cin >> s >> t;
    if (s.size() != t.size()) {
        cout << "-1\n";
        return 0;
    } else if (s == t) {
        cout << "0\n";
        return 0;
    } 

    for (int i = 0; i < s.size(); i++) {
        alpha[s[i] - 'a']++;
        alpha[t[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (alpha[i] != 0) {
            cout << "-1\n";
            return 0;
        }
    }
}
