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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int sz;
pair<ll, ll> chull[MAXN];

ll cross(pair<ll, ll> &v1, pair<ll, ll> &v2) {
    return v1.first * v2.second - v1.second * v2.first;
}

bool cw(pair<ll, ll> &a, pair<ll, ll> &b, pair<ll, ll> &c) {
    pair<ll, ll> v1 = {b.first - a.first, b.second - a.second};
    pair<ll, ll> v2 = {c.first - b.first, c.second - b.second};
    return cross(v1, v2) < 0;
}

void solve() {
    int n; cin >> n;
    sz = 0;
    for (int i = 0; i < n; i++) {
        ll y; cin >> y;
        pair<ll, ll> pt = {i, y};
        while (sz > 1 && !cw(chull[sz - 2], chull[sz - 1], pt)) {
            sz--;
        }
        chull[sz++] = pt;
    }

    ll ans = 0;
    for (int i = 0; i < sz - 1; i++) {
        ans = max(ans, chull[i + 1].first - chull[i].first);
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
