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

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

constexpr int MOD1 = 1000000007;
constexpr int MOD2 = 1000000009;

template<int MOD>
struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi (ll _v) : v(_v % MOD) {}

#define OP(op, typ) \
    mi operator op (const mi<MOD> &other) const { return mi((typ) v op other.v); } \
    mi &operator op##= (const mi<MOD> &other) { return *this = *this op other; }
    OP(+, int); OP(-, int); OP(*, ll);

    bool operator==(const mi &other) const {
        return v == other.v;
    }

    mi pow(ll e) {
        mi cur = *this;
        mi res = 1;
        while (e) {
            if (e & 1) res *= cur;
            cur *= cur;
            e >>= 1;
        }
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

/*
using info = pair<mi<MOD1>, mi<MOD2>>;

#define OP2(op) \
    info operator op(const info &i1, const info &i2) { \
        return {i1.first op i2.first, i1.second op i2.second}; \
    } \
    info &operator op##= (info &i1, const info &i2) { \
        return i1 = i1 op i2; \
    }
OP2(+); OP2(-); OP2(*); 
*/
using info = mi<1000000007>;

info base = {12094};

vector<info> base_pows;
vector<info> psum;

template<bool FORW>
struct hash2 {
    info h;
    int len{};

    hash2 comb(const hash2 &other) const {
        info nh;
        if (FORW) {
            nh = h + other.h * base_pows[len];
        } else {
            nh = h * base_pows[other.len] + other.h;
        }
        return {nh, len + other.len};
    }
};

template<bool FORW>
struct segtree {
    int n;
    vector<hash2<FORW>> st;
    vector<int> lazy;

    segtree(int _n) : n(_n), st(4 * n), lazy(4 * n) { build(1, 0, n); }

#define lc 2*v
#define rc 2*v+1
#define m (l + r) / 2

    void build(int v, int l, int r) {
        if (r - l == 1) {
            st[v].len = 1;
        } else {
            build(lc, l, m);
            build(rc, m, r);
            st[v].len = st[lc].len + st[rc].len;
        }
    }

    void push(int v, int l, int r) {
        if (r - l > 1) {
            lazy[lc] += lazy[v];
            lazy[rc] += lazy[v];
        }
        auto sumpows = psum[r - l];
        st[v].h += sumpows * info{lazy[v]};
        lazy[v] = 0;
    }

    void upd(int x, int y, int q) { upd(1, 0, n, x, y, q); }
    void upd(int v, int l, int r, int x, int y, int q) {
        push(v, l, r);
        if (r <= x || y <= l) return;
        if (x <= l && r <= y) {
            lazy[v] += q;
            push(v, l, r);
        } else {
            upd(lc, l, m, x, y, q);
            upd(rc, m, r, x, y, q);
            st[v] = st[lc].comb(st[rc]);
        }
    }

    hash2<FORW> qry(int x, int y) { return qry(1, 0, n, x, y); }
    hash2<FORW> qry(int v, int l, int r, int x, int y) {
        push(v, l, r);
        if (r <= x || y <= l) return hash2<FORW>{};
        if (x <= l && r <= y) {
            return st[v];
        } else {
            return qry(lc, l, m, x, y).comb(
                qry(rc, m, r, x, y)
            );
        }
    }

#undef lc
#undef rc
#undef m
};

void precomp(int n) {
    base_pows.push_back(info{1});
    while (sz(base_pows) <= n) {
        base_pows.push_back(base_pows.back() * base);
    }

    info cur = info{0};
    psum.push_back(cur);

    rep(i, 0, sz(base_pows)) {
        cur += base_pows[i];
        psum.push_back(cur);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q, k, b;
    cin >> n >> q >> k >> b;
    precomp(n);

    vector<int> a(n);
    rep(i, 0, n) {
        cin >> a[i];
        a[i] = 2 * a[i] - i * k;
    }

    segtree<true> st_forw(n);
    segtree<false> st_back(n);
    rep(i, 0, n) {
        st_forw.upd(i, i+1, a[i]);
        st_back.upd(i, i+1, a[i]+2*b);
    }

    while (q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int l, r, v;
            cin >> l >> r >> v;
            l--;
            st_forw.upd(l, r, 2*v);
            st_back.upd(l, r, 2*v);
        } else {
            int i;
            cin >> i;
            i--;

            auto check = [&](int r) {
                if (i - r >= 0 && i + r < n) {
                    auto forw = st_forw.qry(i+1, i + r + 1);
                    auto back = st_back.qry(i - r, i);
                    return forw.h == back.h;
                }
                return false;
            };

            int lo = 0;
            int hi = n;
            int ans = 0;
            while (lo <= hi) {
                int m = (lo + hi) / 2;
                if (check(m)) {
                    ans = m;
                    lo = m + 1;
                } else {
                    hi = m - 1;
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}
