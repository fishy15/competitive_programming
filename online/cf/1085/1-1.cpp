#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int maxi = count(all(s), '1');
    rep(i, 1, n-1) {
        if (s[i] == '0' && s[i-1] == '1' && s[i+1] == '1') {
            maxi++;
            s[i] = '1';
        }
    }

    int grp = 0;
    int mini = 0;
    rep(i, 0, n) {
        if (s[i] == '1') {
            grp++;
        } else {
            mini += (grp - 1) / 2;
            grp = 0;
        }
    }

    mini += (grp - 1) / 2;

    cout << maxi - mini << ' ' << maxi << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
