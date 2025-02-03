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
#include <cassert>

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

// assumes false and then true
template<typename F>
ll find_first(ll l, ll r, F f) {
    ll ans = r+1;
    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (f(m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return ans;
}

#ifdef LOCAL
ll real_a, real_b, real_c;

ll ask(ll l, ll r) {
    cout << "xor " << l << ' ' << r << endl;
    ll res = 0;
    if (l <= real_a && real_a <= r) {
        res ^= real_a;
    }
    if (l <= real_b && real_b <= r) {
        res ^= real_b;
    }
    if (l <= real_c && real_c <= r) {
        res ^= real_c;
    }
    return res;
}
void ans(ll a, ll b, ll c) {
    cout << "ans " << a << ' ' << b << ' ' << c << endl;
    if (a == real_a && b == real_b && c == real_c) {
        cout << "works\n";
    } else {
        cout << "failed\n";
    }
}
#else
ll ask(ll l, ll r) {
    cout << "xor " << l << ' ' << r << endl;
    ll x;
    cin >> x;
    if (x == -1) {
        exit(0);
    }
    return x;
}
void ans(ll a, ll b, ll c) {
    cout << "ans " << a << ' ' << b << ' ' << c << endl;
}
#endif

void solve() {
    ll n;
    cin >> n;

#ifdef LOCAL
    cin >> real_a >> real_b >> real_c;
#endif

    auto total = ask(1, n);
    if (total == 0) {
        ll cur_p = 1;
        while (2 * cur_p <= n) {
            cur_p *= 2;
        }

        ll a;
        while (true) {
            a = ask(1, cur_p-1);
            if (a != 0) {
                break;
            }

            // recurse into the left half
            cur_p /= 2;
        }

        auto b = find_first(cur_p, n, [&](ll end) { return ask(cur_p, end) != 0; });
        auto c = a ^ b;
        ans(a, b, c);
    } else {
        auto a = find_first(1, n, [&](ll end) { return ask(1, end) != 0; });
        auto c = find_first(1, n, [&](ll start) { return ask(start, n) == 0; }) - 1;
        auto b = total ^ a ^ c;
        ans(a, b, c);
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
