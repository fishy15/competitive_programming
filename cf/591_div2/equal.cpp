// :pray: :steph:
// :pray: :bakekaga:

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

void solve() {
    string s1, s2; cin >> s1 >> s2;
    vector<int> f(26), s(26);

    for (char &c : s1) {
        f[c - 'a'] = 1;
    }

    for (char &c : s2) {
        s[c - 'a'] = 1;
    }

    for (int i = 0; i < 26; i++) {
        if (f[i] && s[i]) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    int q; cin >> q;
    while (q--) {
        solve();
    }

    return 0;
}
