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
#include <chrono>
#include <random>

#define ll long long
#define ld long double
#define eps 1e-8

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define MethodToTemplateLambda(method) \
    template<typename T>               \
    struct method##_t {                \
        auto operator()(T x) {         \
            return x. method ();       \
        }                              \
    };                                 \

using namespace std;

constexpr int MOD1 = 1000000007;
constexpr int MOD2 = 1000000009;
constexpr int MAXN = 200000;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<int MOD>
struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= MOD) v -= MOD;
        if (v < 0) v += MOD;
    }
    mi(ll _v) : mi((int)(_v % MOD)) {}
    mi operator+(const mi &m2) const { return mi(v + m2.v); }
    mi operator-(const mi &m2) const { return mi(v - m2.v); }
    mi operator*(const mi &m2) const { return mi((ll) v * m2.v); }
    mi operator/(const mi &m2) const { return mi((ll) v * m2.inv().v); }
    mi &operator+=(const mi &m2) { return *this = *this + m2; }
    mi &operator-=(const mi &m2) { return *this = *this - m2; }
    mi &operator*=(const mi &m2) { return *this = *this * m2; }
    mi &operator/=(const mi &m2) { return *this = *this / m2; }
    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e > 0) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() const {
        return pow(MOD - 2);
    }
};

template<typename T, typename U>
struct parallel_pair {
    T first;
    U second;
    parallel_pair() : first{}, second{} {}
    parallel_pair(T x, U y) : first{x}, second{y} {}

#define OP(op, apply_op)                                                  \
    auto operator op(const parallel_pair<T, U> &other) const {            \
        return parallel_pair{first op other.first, second op other.second}; \
    }                                                                     \
    auto &operator apply_op(const parallel_pair<T, U> &other) {           \
        return *this = *this op other;                                    \
    }

    OP(+, +=);
    OP(-, -=);
    OP(*, *=);
    OP(/, /=);
#undef OP

    template<template<typename> typename F>
    auto call() {
        return parallel_pair{F<T>{}(first), F<U>{}(second)};
    }

    template<template<typename> typename F, typename Input>
    auto call(Input x) {
        return parallel_pair{F<T>{}(first, x), F<U>{}(second, x)};
    }
};

using hash_state = parallel_pair<mi<MOD1>, mi<MOD2>>;

template<typename node>
struct segtree {
    int n;
    vector<node> st;

    segtree(int n) : n(n), st(2 * n) {}
    segtree(vector<node> &nums) : segtree(nums.size()) { 
        copy(nums.begin(), nums.end(), st.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            st[i] = st[i << 1] + st[i << 1 | 1];
        }
    }

    void upd(int x, node y) { 
        x += n;
        st[x] = y;
        while (x > 1) {
            st[x >> 1] = st[x] + st[x ^ 1];
            x >>= 1;
        }
    }

    node qry(int l, int r) const {
        node ans{};
        l += n;
        r += n;
        while (l < r) {
            if (l & 1) {
                ans = ans + st[l];
                l++;
            }

            if (r & 1) {
                r--;
                ans = ans + st[r];
            }

            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
};

array<hash_state, MAXN + 1> pow_cache;
array<hash_state, MAXN + 1> inv_pow_cache;

MethodToTemplateLambda(inv);

void precalc() {
    pow_cache[0] = {1, 1};
    hash_state mul{
        uniform_int_distribution(2, MOD1-1)(rng),
        uniform_int_distribution(2, MOD2-1)(rng),
    };

    for (int i = 1; i <= MAXN; i++) {
        pow_cache[i] = pow_cache[i - 1] * mul;
    }

    inv_pow_cache[MAXN] = pow_cache[MAXN].call<inv_t>();

    for (int i = MAXN - 1; i >= 0; i--) {
        inv_pow_cache[i] = inv_pow_cache[i + 1] * mul;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    vector<hash_state> forw(n);
    vector<hash_state> back(n);
    for (int i = 0; i < n; i++) {
        auto v = s[i] - 'a' + 1;
        forw[i] = pow_cache[i].call<multiplies>(v);
        back[i] = pow_cache[n - i - 1].call<multiplies>(v);
    }

    segtree forw_st(forw);
    segtree back_st(back);

    auto qry_forw = [&forw_st](int l, int r) {
        return forw_st.qry(l, r) * inv_pow_cache[l];
    };

    auto qry_back = [&back_st, n](int l, int r) {
        return back_st.qry(l, r) * inv_pow_cache[n - r];
    };

    while (m--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            char x;
            cin >> k >> x;
            k--;

            auto v = x - 'a' + 1;
            forw_st.upd(k, pow_cache[k].call<multiplies>(v));
            back_st.upd(k, pow_cache[n - k - 1].call<multiplies>(v));
        } else {
            int l, r;
            cin >> l >> r;
            l--;

            auto res1 = qry_forw(l, r);
            auto res2 = qry_back(l, r);

            if (res1.first.v == res2.first.v && res1.second.v == res2.second.v) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }

    return 0;
}
