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
#define MOD 998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

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

ll isqrt(ll x) {
    auto sq = (ll) sqrt(x);
    while (sq * sq > x) sq--;
    while ((sq + 1) * (sq + 1) <= x) sq++;
    return sq;
}

mi tri(int x) {
    static mi div2 = mi(2).inv();
    return mi(x) * (x + 1) * div2;
}

void solve() {
    int n;
    cin >> n;

    vector<int> s(n);
    rep(i, 0, n) {
        cin >> s[i];
    }

    vector<mi> psum(s[n-1] + 1);
    for (auto x : s) {
        psum[x] += 1;
    }
    rep(i, 1, s[n-1]+1) {
        psum[i] += psum[i - 1];
    }

    mi ans = 0;

    // check factors
    rep(i, 1, s[n-1]+1) {
        if (s[n-1] % i == 0) {
            int cnt = 0;
            for (auto x : s) {
                if (x % i == 0) {
                    cnt++;
                }
            }
            ans += mi(cnt) * (s[n-1] / i);
        }
    }

    auto comp = [&](ll x) {
        mi cnt = 0;
        for (int mul = 1; mul < x && x * mul <= s[n-1]; mul++) {
            int base = x * mul;
            cnt += psum[min(s[n-1], base + mul)] - psum[base - 1];
        }
        if (x * x <= s[n-1]) {
            cnt += psum.back() - psum[x * x - 1];
        }
        return cnt;
    };

    // check 
    auto sq = isqrt(s[n-1]);
    rep(i, 1, sq+1) {
        if (s[n-1] % i != 0 && s[n-1] / i > sq) {
            // if x = i
            auto lo = s[n-1] / i;
            auto cnt = comp(lo);
            ans += cnt * i;
        }

        // x such that floor(s_n / x) = i, ceil(s_n / x) = i + 1
        // x*i < s_n < x(i+1)
        // s_n / (i + 1) < x < s_n / i
        auto l = (s[n-1] + (i + 1) - 1) / (i + 1);
        if (s[n-1] % l == 0) {
            l++;
        }

        auto r = s[n-1] / i;
        if (s[n-1] % r == 0) {
            r--;
        }

        if (l <= r) {
            auto cnt = comp(i);
            ans += (tri(r) - tri(l-1)) * cnt;
        }
    }

    cout << ans.v << '\n';
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
