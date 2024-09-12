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

struct info {
    int value;
    int count;
    int start_idx;
};

constexpr int L = 20;

bool is_power_2(int x) {
    return (x & (x - 1)) == 0;
}

ll tri(ll x) {
    return x * (x + 1) / 2;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    vector<info> comp;
    rep(i, 0, n) {
        if (comp.empty() || comp.back().value != a[i]) {
            comp.push_back({a[i], 1, i});
        } else {
            comp.back().count++;
        }
    }

    vector<array<int, L>> diff(sz(comp) - 1);
    rep(i, 0, sz(comp) - 1) {
        diff[i][0] = abs(comp[i + 1].value - comp[i].value);
    }

    rep(p, 1, L) {
        rep(i, 0, n) {
            if (i + (1 << p) <= sz(diff)) {
                diff[i][p] = gcd(diff[i][p - 1], diff[i + (1 << (p - 1))][p - 1]);
            }
        }
    }

    ll ans = 0;
    rep(i, 0, sz(comp)) {
        ans += tri(comp[i].count);
        if (i < sz(comp) - 1) {
            int cur_gcd = 0;
            int loc = i;
            for (int p = L - 1; p >= 0; p--) {
                if (loc + (1 << p) <= sz(diff)) {
                    auto nxt_gcd = gcd(cur_gcd, diff[loc][p]);
                    if (!is_power_2(nxt_gcd)) {
                        cur_gcd = nxt_gcd;
                        loc += 1 << p;
                    }
                }
            }
            if (loc + 1 < sz(comp)) {
                ans += (ll) comp[i].count * (n - comp[loc + 1].start_idx);
            }
        }
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
