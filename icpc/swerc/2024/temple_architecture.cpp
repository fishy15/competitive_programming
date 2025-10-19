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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<pair<ll, int>> h(n);
    rep(i, 0, n) {
        cin >> h[i].first;
        h[i].second = i;
    }

    sort(all(h), greater<>{});

    set<int> big;
    ll ans = 0;
    for (auto [_, x] : h) {
        auto it = big.lower_bound(x);
        ll d = INFLL;
        if (it != end(big)) {
            d = min<ll>(d, *it - x);
        }
        if (it != begin(big)) {
            d = min<ll>(d, x - *prev(it));
        }
        big.insert(x);
        if (d != INFLL) {
            ans += d;
        }
    }

    cout << ans << '\n';

    return 0;
}
