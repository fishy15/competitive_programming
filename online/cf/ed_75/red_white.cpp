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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 300010

using namespace std;

ll modpow(ll n, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * n % MOD;
        n = n * n % MOD;
        e >>= 1;
    }
    return res;
}

struct ntt {
    const int logn = 20;
    const int sz = 1 << logn;
    const ll g = 3;
    vector<vector<ll>> w;
    vector<vector<ll>> invw;
    vector<vector<int>> rev;
    ntt() {
        ll wpow = modpow(g, (MOD - 1) / (1 << logn));
        w.resize(logn + 1);
        invw.resize(logn + 1);
        rev.resize(logn + 1);
        for (int i = 0; i < logn; i++) {
            w[i].resize(1 << i);
            invw[i].resize(1 << i);
            rev[i].resize(1 << i);
            ll m = modpow(wpow, (1 << (logn - i - 1)));
            ll invm = modpow(m, MOD - 2);
            w[i][0] = 1;
            invw[i][0] = 1;
            for (int j = 1; j < (1 << i); j++) {
                w[i][j] = w[i][j - 1] * m % MOD;
                invw[i][j] = invw[i][j - 1] * invm % MOD;
            }
            if (i == 0) continue;
            for (int j = 1, k = 0; j < (1 << i); j++) {
                int bit = 1 << (i - 1);
                for (; k & bit; bit /= 2) k ^= bit;
                k ^= bit;
                if (j < k) rev[i][j] = k;
            }
        }
    }
    void ntt_calc(vector<ll> &a, int ln, int n, bool invert) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            if (i < rev[ln][i]) swap(a[i], a[rev[ln][i]]);
        }
        for (int i = 1; i <= ln; i++) {
            int len = 1 << i;
            for (int j = 0; j < n; j += len) {
                for (int k = 0; k < len / 2; k++) {
                    ll mul = invert ? invw[i - 1][k] : w[i - 1][k];
                    ll u = a[j + k];
                    ll v = a[j + k + len / 2] * mul % MOD;
                    a[j + k] = (u + v) % MOD;
                    a[j + k + len / 2] = (u - v + MOD) % MOD;
                }
            }
        }
        if (invert) {
            ll inv = modpow(n, MOD - 2);
            for (int i = 0; i < n; i++) {
                a[i] = a[i] * inv % MOD;
            }
        }
    }
    void mul(vector<ll> &a, vector<ll> &b, vector<ll> &c) {
        int n = 1;
        int ln = 0;
        while (n < (a.size() + b.size())) {
            n *= 2;
            ln++;
        }
        a.resize(n);
        b.resize(n);
        c.resize(n);
        ntt_calc(a, ln, n, false);
        ntt_calc(b, ln, n, false);
        for (int i = 0; i < n; i++) {
            c[i] = a[i] * b[i] % MOD;
        }
        ntt_calc(c, ln, n, true);
    }
};

int n, k, q;
int white[MAXN];
map<int, int> cnt;
int red[10];
int qq[MAXN];
ll ans[MAXN];

ll f[MAXN];
ll inv[MAXN];
ntt ntt;

ll c(ll nn, ll kk) {
    return f[nn] * inv[kk] % MOD * inv[nn - kk] % MOD;
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> white[i];
        cnt[white[i]]++;
    }

    for (int i = 0; i < k; i++) {
        cin >> red[i];
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> qq[i];
    }

    f[0] = 1;
    inv[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i % MOD;
        inv[i] = modpow(f[i], MOD - 2);
    }

    for (int i = 0; i < k; i++) {
        int one = 0;
        int two = 0;

        for (auto p : cnt) {
            if (p.first >= red[i]) break;
            if (p.second == 1) one++;
            else two++;
        }

        vector<ll> polyone;
        vector<ll> polytwo;

        ll curpow = 1;
        for (int j = 0; j <= one; j++) {
            polyone.push_back(c(one, j) * curpow % MOD);
            curpow = curpow * 2 % MOD;
        }

        for (int j = 0; j <= 2 * two; j++) {
            polytwo.push_back(c(2 * two, j));
        }

        vector<ll> res;
        ntt.mul(polyone, polytwo, res);
        for (int j = 0; j < q; j++) {
            int need = qq[j] / 2 - red[i] - 1;
            if (need >= 0 && need < res.size()) {
                ans[j] += res[need];
                if (ans[j] >= MOD) ans[j] -= MOD;
            }
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
