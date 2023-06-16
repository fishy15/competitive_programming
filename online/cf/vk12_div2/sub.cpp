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

ll solve(string &s1, string &s2) {
    string s = s1 + '.' + s2;
    int n = (int)(s.size());

    vector<int> z(n);
    int l = 0;
    int r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    ll ans = 0;
    for (int i = s1.size() + 1; i < n; i++) {
        ans += (z[i] != 0);
        if (ans > MOD) ans -= MOD;
    }
    return ans;
}

int main() {
    cin.tie(0); ios::sync_with_stdio(0);

    string s1, s2; cin >> s1 >> s2;
    ll ans = 0;
    for (int i = 0; i < s1.size(); i++) {
        string s = s1.substr(i, s1.size() - i);
        ans += solve(s, s2);
        cout << solve(s, s2) << '\n';
        if (ans > MOD) ans -= MOD;
    }

    cout << ans << '\n';

    return 0;
}
