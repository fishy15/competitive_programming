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
    int n, k;
    ll x;
    cin >> n >> k >> x;
    x--;

    string s;
    cin >> s;

    vector<int> groups;
    int cur = 0;
    rep(i, 0, n) {
        if (s[i] == 'a') {
            if (cur > 0) {
                groups.push_back(cur);
                cur = 0;
            }
        } else {
            cur++;
        }
    }

    if (cur > 0) {
        groups.push_back(cur);
    }

    vector<__int128_t> group_make(sz(groups));
    __int128_t can_make = 1;
    for (int i = sz(groups) - 1; i >= 0; i--) {
        group_make[i] = can_make;
        if (can_make <= x) {
            can_make *= (groups[i] * k + 1);
        }
    }

    vector<int> need(sz(groups));
    rep(i, 0, sz(groups)) {
        if (group_make[i] <= x) {
            need[i] = x / group_make[i];
            x %= group_make[i];
        }
    }

    int group_num = 0;
    cur = 0;
    rep(i, 0, n) {
        if (s[i] == 'a') {
            if (cur > 0) {
                rep(_, 0, need[group_num]) cout << 'b';
                group_num++;
                cur = 0;
            }
            cout << 'a';
        } else {
            cur++;
        }
    }

    if (cur > 0) {
        rep(_, 0, need[group_num]) cout << 'b';
    }

    cout << '\n';
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
