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

    map<int, int> cnt;
    rep(i, 0, n) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<pair<int, int>> odds;
    ll alice = 0;
    ll bob = 0;
    for (auto [x, c] : cnt) {
        if (x % 2 == 1) {
            odds.push_back({x, c});
        } else {
            alice += (ll) x * c / 2;
            bob += (ll) x * c / 2;
        }
    }

    sort(all(odds), [](auto a, auto b) { return a.second > b.second; });
    rep(i, 0, sz(odds)) {
        auto [x, c] = odds[i];
        if (i % 2 == 0) {
            alice += (ll) c * ((x + 1) / 2);
            bob += (ll) c * (x / 2);
        } else {
            bob += (ll) c * ((x + 1) / 2);
            alice += (ll) c * (x / 2);
        }
    }

    cout << alice << ' ' << bob << '\n';
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
