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
#include <optional>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

optional<ll> pow(ll n, ll x, ll limit) {
    ll res = 1;
    for (ll i = 0; i < x; i++) {
        res *= n;
        if (res > limit) return {};
    }
    return res;
}

void solve() {
    ll n;
    cin >> n;

    if (n % 2 == 0) {
        cout << 1 << ' ' << n / 2 << '\n';
    } else {
        cout << "-1\n";
    }
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
