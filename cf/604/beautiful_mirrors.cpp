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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, q;
ll p[MAXN];
ll num_p[MAXN];
ll denom_p[MAXN];

ll ans;
map<int, ll> cur;

ll modpow(ll n, ll e, ll m) {
    if (e == 0) return 1LL;
    if (e == 1) return n % m;
    ll res = modpow(n, e / 2, m);
    if (e % 2) {
        return (res * res % m) * n % m;
    }
    return res * res % m;
}

ll get_num(int start, int end) {
    /* cout << start << ' ' << end << '\n'; */
    ll res = num_p[end - 2];
    if (start == 1) return res;

    res -= num_p[start - 2];
    if (res < 0) res += MOD;
    res *= modpow(denom_p[start - 1], MOD - 2, MOD);
    /* cout << "result: " << res % MOD << '\n'; */
    return res % MOD;
}

ll get_denom(int start, int end) {
    return denom_p[end - 1] * modpow(denom_p[start - 1], MOD - 2, MOD) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    p[0] = modpow(100, MOD - 2, MOD);

    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        p[i] *= p[0];
        p[i] %= MOD;
    }

    denom_p[0] = 1;
    for (int i = 1; i <= n; i++) {
        denom_p[i] = denom_p[i - 1] * p[i] % MOD;
    }

    num_p[0] = 1;
    for (int i = 1; i <= n; i++) {
        num_p[i] = (num_p[i - 1] + denom_p[i]) % MOD;
    }

    // calculate initial
    cur[1] = num_p[n - 1] * modpow(denom_p[n], MOD - 2, MOD) % MOD;
    ans = cur[1];

    /* cout << "init" << get_num(1, n + 0) * modpow(get_denom(1, n + 0), MOD - 2, MOD) % MOD << '\n'; */

    cur[n + 1] = 0;

    for (int i = 0; i < q; i++) {
        int u; cin >> u;
        if (cur.count(u)) {
            auto it = cur.find(u);
            auto prev = it;
            auto forw = it;
            prev--;
            forw++;

            ans -= it->second;
            if (ans < 0) ans += MOD;
            ans -= prev->second;
            if (ans < 0) ans += MOD;

            /* cout << "rem: " << ans << '\n'; */

            cur.erase(it);
            int p = prev->first;
            int f = forw->first;
            prev->second = get_num(p, f) * modpow(get_denom(p, f), MOD - 2, MOD) % MOD;
            ans += prev->second;
            if (ans >= MOD) ans -= MOD;
        } else {
            cur[u] = 0;
            auto it = cur.find(u);
            auto prev = it;
            auto forw = it;
            prev--;
            forw++;

            ans -= prev->second;
            if (ans < 0) ans += MOD;

            /* cout << "rem: " << ans << '\n'; */

            int p = prev->first;
            int f = forw->first;
            prev->second = get_num(p, u) * modpow(get_denom(p, u), MOD - 2, MOD) % MOD;
            ans += prev->second;
            if (ans >= MOD) ans -= MOD;

            cur[u] = get_num(u, f) * modpow(get_denom(u, f), MOD - 2, MOD) % MOD;
            ans += cur[u];
            if (ans >= MOD) ans -= MOD;
        }

        /* cout << i << ":\n"; */
        /* for (auto p : cur) { */
        /*     cout << p.first << ' ' << p.second << '\n'; */
        /* } */

        cout << ans << '\n';
    }

    return 0;
}
