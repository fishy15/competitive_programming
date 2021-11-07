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

// change if necessary
#define MAXN 1000000

using namespace std;

ll mod(ll a, ll b) {
    ll res = a % b;
    if (res < 0) res += b;
    return res;
}

ll check(ll r, ll g, ll b, ll v1, ll v2, ll v3) {
    ll mod1 = mod(r - v1, 3);
    ll mod2 = mod(g - v2, 3);
    ll mod3 = mod(b - v3, 3);

    if (mod1 != mod2 || mod1 != mod3 || mod2 != mod3) {
        return INFLL;
    }

    ll min_m = max({0LL, r - v1, g - v2, b - v3});

    ll cur_mod = mod(v1 + min_m - r, 3);
    if (cur_mod == 0) {
        return min_m;
    } else if (cur_mod == 1) {
        return min_m + 2;
    } else {
        return min_m + 1;
    }
}

void solve() {
    ll r, g, b; cin >> r >> g >> b;
    ll sum = r + g + b;

    ll moves = check(r, g, b, sum, 0, 0);
    moves = min(moves, check(r, g, b, 0, sum, 0));
    moves = min(moves, check(r, g, b, 0, 0, sum));

    if (moves == INFLL) {
        cout << "-1\n";
    } else {
        cout << moves << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
