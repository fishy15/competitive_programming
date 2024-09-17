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
#define mod 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

ll modpow(ll b, ll e, ll m=mod) {
    ll ans = 1;
    for (; e; b = b * b % m, e /= 2)
        if (e & 1) ans = ans * b % m;
    return ans;
}

typedef vector<int> vi;

const ll root = 62;
//
//
typedef vector<ll> vl;
void ntt(vl &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, modpow(root, mod >> s)};
        rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
            ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
            a[i + j + k] = ai - z + (z > ai ? mod : 0);
            ai += (ai + z >= mod ? z - mod : z);
        }
}
vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
        n = 1 << B;
    int inv = modpow(n, mod - 2);
    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i,0,n)
        out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}

vl myconv(const vl &a, const vl &b, int p) {
    auto res = conv(a, b);
    vl out(p - 1);
    rep(i, 0, sz(res)) {
        (out[i % (p - 1)] += res[i]) %= mod;
    }
    return out;
}

vector<int> gen_list(int p) {
    rep(i, 1, p) {
        vector<bool> vis(p);
        vector<int> gend = {1};
        vis[1] = true;
        while (true) {
            auto nxt = gend.back() * i % p;
            if (vis[nxt]) break;
            vis[nxt] = true;
            gend.push_back(nxt);
        }

        if (sz(gend) == p - 1) {
            return gend;
        }
    }

    return {};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string k;
    int p, x;
    cin >> k >> p >> x;

    vector<ll> f(p + 1);
    vector<ll> inv(p + 1);
    f[0] = inv[0] = 1;
    rep(i, 1, p+1) {
        f[i] = f[i - 1] * i % p;
        inv[i] = modpow(f[i], p - 2, p);
    }

    auto c = [&](int n, int k2) {
        if (n < k2) return 0LL;
        return f[n] * inv[k2] % p * inv[n - k2] % p;
    };

    // set up poly
    vl counts(p);
    rep(i, 0, p) {
        rep(j, 0, p) {
            counts[c(i, j)]++;
        }
    }

    auto gg = gen_list(p);
    vl poly(p - 1);
    rep(i, 0, sz(gg)) {
        poly[i] = counts[gg[i]];
    }

    auto cur = poly;
    cur.resize(p - 1);
    vl ans = {1};
    ans.resize(p - 1);
    for (int i = sz(k) - 1; i >= 0; i--) {
        if (k[i] == '1') ans = myconv(cur, ans, p);
        cur = myconv(cur, cur, p);
    }

    auto idx = find(all(gg), x) - begin(gg);

    cout << ans[idx] << '\n';

    return 0;
}
