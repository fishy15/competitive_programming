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

void solve() {
    ll n, k, w; cin >> n >> k >> w;
    vector<ll> l, h;
    for (int i = 0; i < k; i++) {
        ll x; cin >> x;
        l.push_back(x);
    }
    ll a_l, b_l, c_l, d_l; cin >> a_l >> b_l >> c_l >> d_l;
    for (int i = k; i < n; i++) {
        l.push_back(((a_l * l[i - 2] % d_l + b_l * l[i - 1] % d_l) % d_l + c_l % d_l) % d_l + 1);
    }
    for (int i = 0; i < k; i++) {
        ll x; cin >> x;
        h.push_back(x);
    }
    ll a_h, b_h, c_h, d_h; cin >> a_h >> b_h >> c_h >> d_h;
    for (int i = k; i < n; i++) {
        h.push_back(((a_h * h[i - 2] % d_h + b_h * h[i - 1] % d_h) % d_h + c_h % d_h) % d_h + 1);
    }

    ll cur_l = -1;
    ll cur_r = -1;
    ll prev_p = 0;
    ll cur_p = 0;
    ll ans = 1;

    for (auto x : l) cout << x << ' ';
    cout << '\n';
    for (auto x : h) cout << x << ' ';
    cout << '\n';

    for (int i = 0; i < n; i++) {
        if (l[i] <= cur_r) {
            cur_p += 2 * (l[i] + w - cur_r);
            cur_r = l[i] + w;
            if (h[i - 1] < h[i]) {
                cur_p += 2 * (h[i] - h[i - 1]);
            }
            cur_p %= MOD;
        } else {
            if (i > 0) {
                prev_p += cur_p;
                prev_p %= MOD;
            }
            cur_l = l[i];
            cur_r = l[i] + w;
            cur_p = 2 * (cur_r - cur_l + h[i]) % MOD;
        }
        ans *= (prev_p % MOD + cur_p % MOD) % MOD;
        ans %= MOD;
        cout << prev_p << ' ' << cur_p << '\n';
    }

    cout << ans << '\n';
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
