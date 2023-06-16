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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

inline ll sum(ll n) {
    return n * (n + 1) / 2;
}

inline ll sum_odd(ll n) {
    n = (n + 1) / 2;
    return n * n;
}

inline ll sum_even(ll n) {
    n = n / 2;
    return n * (n + 1);
}

void solve() {
    ll l, r; cin >> l >> r;
    bool ss = false;
    if (l < r) {
        ss = true;
        swap(l, r);
    }

    int d = l - r;

    // equalize them somewhat
    ll used = 0;
    ll lb = 1;
    ll rb = 3e9;
    ll ans = -1;
    while (lb <= rb) {
        int m = lb + (rb - lb) / 2;
        if (sum(m) <= d) {
            ans = m;
            lb = m + 1;
        } else {
            rb = m - 1;
        }
    }

    if (sum(ans + 1) > l) {
        cout << ans << ' ';
        l -= sum(ans);
        if (ss) swap(l, r);
        cout << l << ' ' << r << '\n';
        return;
    }

    if (d == sum(ans)) ss = false;

    used = ans + 1;
    l -= sum(ans + 1);
    if (l < r) {
        ss = !ss;
        swap(l, r);
    }

    if (used % 2 == 0) {
        // higher side is at odd, higher is l
        ll lb = 0;
        ll rb = 3e9;
        ll ans = -1;
        while (lb <= rb) {
            ll m = lb + (rb - lb) / 2;
            if (sum_even(used + 2 * m) - sum_even(used) <= r) {
                ans = m;
                lb = m + 1;
            } else {
                rb = m - 1;
            }
        }
        r -= sum_even(used + 2 * ans) - sum_even(used);
        l -= sum_odd(used + 2 * ans - 1) - sum_odd(used - 1);
        used += 2 * ans;
        if (l - used - 1 >= 0) {
            l -= used + 1;
            used++;
        }

        cout << used << ' ';
        if (ss) {
            swap(l, r);
        }
        cout << l << ' ' << r << '\n';
    } else {
        // higher side is at even, higher is l
        ll lb = 0;
        ll rb = 3e9;
        ll ans = -1;
        while (lb <= rb) {
            ll m = lb + (rb - lb) / 2;
            if (sum_odd(used + 2 * m) - sum_odd(used) <= r) {
                ans = m;
                lb = m + 1;
            } else {
                rb = m - 1;
            }
        }
        r -= sum_odd(used + 2 * ans) - sum_odd(used);
        l -= sum_even(used + 2 * ans - 1) - sum_even(used - 1);
        used += 2 * ans;
        if (l - used - 1 >= 0) {
            l -= used + 1;
            used++;
        }

        cout << used << ' ';
        if (ss) {
            swap(l, r);
        }
        cout << l << ' ' << r << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
