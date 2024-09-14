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

ll mm(ll x, ll m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

void solve() {
    ll n, k, w, h;
    cin >> n >> k >> w >> h;

    string s;
    cin >> s;

    vector<pair<ll, ll>> locs;
    locs.push_back({0, 0});

    rep(i, 0, n) {
        auto [x, y] = locs.back();
        auto d = s[i];
        if (d == 'U') y++;
        else if (d == 'D') y--;
        else if (d == 'L') x--;
        else x++;
        locs.push_back({x, y});
    }

    // needs to visit 0, 0 mod 2w, 2h
    auto [dx, dy] = locs.back();
    locs.erase(locs.begin());

    map<pair<ll, ll>, ll> cnts;

    auto w2 = 2 * w;
    auto h2 = 2 * h;

    for (auto [x, y] : locs) {
        // when is x + dx * t == 0 && y + dy * t == 0
        // x + dx * t = 0
        // t = -x * dx^{-1} mod 2w
        // t = -y * dy^{-1} mod 2h
        // compute the first 
        cnts[{mm(x, w2), mm(y, h2)}]++;
    }

    ll start_x = 0, start_y = 0;
    ll ans = 0;
    rep(i, 0, k) {
        ll want_x = mm(-start_x, w2);
        ll want_y = mm(-start_y, h2);
        auto it = cnts.find({want_x, want_y});
        if (it != cnts.end()) {
            ans += it->second;
        }
        start_x = mm(start_x + dx, w2);
        start_y = mm(start_y + dy, h2);
    }

    cout << ans << '\n';
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
