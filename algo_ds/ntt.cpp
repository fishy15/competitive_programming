// for mod 998244353
// change g if mod changes (primitive root)
// max logn for a given mod is max power of 2 that divides it

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
