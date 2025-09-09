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

#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using namespace std;

#ifdef LOCAL
ll k, x;
#endif

ll ask(ll l, ll r) {
    cout << "? " << l + 1 << ' ' << r << endl;
#ifdef LOCAL
    bool res = 1 ^ (l <= x && x < r) ^ ((r - l) < k);
    cout << res << endl;
    return res ? 1 : 0;
#else
    ll res;
    cin >> res;
    if (res == -1) {
        exit(0);
    }
    return res;
#endif
}

void answer(ll k) {
    cout << "! " << k << endl;
#ifdef LOCAL
    if (k != ::k) cout << "didnt work" << endl;
#endif
}

void solve() {
    ll n;
    cin >> n;

#ifdef LOCAL
    cin >> k >> x;
    cout << "read these in" << endl;
#endif

    array quarters = {
        ask(0, n / 4),
        ask(n / 4, n / 2),
        ask(n / 2, 3 * n / 4),
        0LL,
    };

    quarters[3] = 1 ^ quarters[0] ^ quarters[1] ^ quarters[2];

    ll one_count = count(all(quarters), 1);

    ll l, r;
    bool big = false;
    if (one_count == 1) {
        // k is greater than a quarter
        l = n / 4;
        r = n - 1;
        big = true;
    } else {
        // k is less than a quarter
        l = 2;
        r = n / 4;
    }

    auto ask_small = [&](ll s) {
        if (quarters[0] == 1 && quarters[1] == 1) {
            return ask(0, s);
        } else {
            return ask(n - s, n);
        }
    };

    auto ask_big = [&](ll s) {
        if (quarters[0] == 1) {
            return ask(0, s);
        } else if (quarters[1] == 1) {
            if (s <= 3 * n / 4) {
                return ask(n / 4, n / 4 + s);
            } else {
                return ask(n - s, n);
            }
        } else if (quarters[2] == 1) {
            if (s <= 3 * n / 4) {
                return ask(3 * n / 4 - s, 3 * n / 4);
            } else {
                return ask(0, s);
            }
        } else {
            return ask(n - s, n);
        }
    };

    ll ans = -1;
    while (l <= r) {
        auto m = (l + r) / 2;
        auto res = big ? ask_big(m) : ask_small(m);
        if ((res == 1) != big) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    answer(ans);
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
