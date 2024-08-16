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

    int n, m;
    cin >> n >> m;

    vector<ll> a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }

    if (m == 2) {
        if (a == b) {
            cout << "0\n";
        } else {
            cout << "-1\n";
        }
        return 0;
    }

    // default c value
    vector<ll> c(n);
    c[0] = b[0];

    auto check = [m](ll x1, ll y1, ll x2, ll y2) {
        return (x1 < x2) == (y1 < y2) && abs(y1 - y2) < m;
    };

    rep(i, 1, n) {
        auto nxt_c1 = c[i - 1] + (b[i] - b[i - 1]);
        if (check(a[i - 1], c[i - 1], a[i], nxt_c1)) {
            c[i] = nxt_c1;
        } else if (check(a[i - 1], c[i - 1], a[i], nxt_c1 - m)) {
            c[i] = nxt_c1 - m;
        } else {
            c[i] = nxt_c1 + m;
        }
    }

    // want to find the best shift
    // |A - (C + x)| => |(A - C) - x|, median A - C
    
    vector<ll> diffs(n);
    rep(i, 0, n) {
        diffs[i] = a[i] - c[i];
    }

    sort(all(diffs));
    auto best = diffs[n / 2];

    // round to the nearest multiple of m
    best = best / m * m;

    auto comp = [&](ll shift) {
        ll tot = 0;
        rep(i, 0, n) {
            auto new_c = c[i] + shift;
            tot += abs(a[i] - new_c);
        }
        return tot;
    };

    ll ans = min({comp(best - m), comp(best), comp(best + m)});

    cout << ans << '\n';

    return 0;
}
