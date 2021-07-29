#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

string rev(string s) {
    return reverse(s.begin(), s.end());
}

int main() {
    int n; cin >> n;
    vector<int> c;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        c.push_back(x);
    }

    vector<string> s;
    string prev = "";

    for (int i = 0; i < n; i++) {
        string s1; cin >> s1;

        if (s1.size() > prev.size()) {
            cout << "-1\n";
            return 0;
        }

        s.push_back(s1);
        prev = s1;
    }

    vector<vector<int>> dp(n, vector<int>(2, 0));

    dp[0][0] = 0;
    dp[0][1] = c[0];

    for (int i = 1; i < n; i++) {
        if (s[i] > s[i - 1]) {
                \
        }

        if (s[i] > rev(s[i - 1])) {

        }

        if (rev(s[i]) > s[i - 1]) {

        }

        if (rev(s[i] > s[i - 1])) {
            
        }
    }
}