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
#include <bitset>

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

using u32 = unsigned int;

u32 disable(u32 m, u32 p) {
    u32 all = -1;
    u32 all_but_p = all ^ (1u << p);
    return m & all_but_p;
}

u32 remove(u32 m, u32 p) {
    u32 keep_p = (1 << (p + 1)) - 1;
    u32 mask_out_p = -1u ^ keep_p;
    return (disable(m, p) & keep_p) | ((m & mask_out_p) >> 1);
}

void solve() {
    int n, m;
    cin >> n >> m;

    int k;
    cin >> k;

    vector<bool> good(n);
    rep(i, 0, k) {
        int c;
        cin >> c;
        c--;
        good[c] = true;
    }

    if (m == 1) {
        cout << "1\n";
        return;
    }

    vector prev_dp = {1, 2};
    vector<int> nxt_dp;
    rep(len, 2, n+1) {
        nxt_dp.resize(1 << len);
        rep(msk, 0, 1 << len) {
            int turn = n - len;
            bool want_max = (turn % 2 == 0);
            int ans = want_max ? -INF : INF;
            rep(pos, 0, len) {
                if (good[pos]) {
                    auto prev_msk = remove(msk, pos);
                    if (want_max) {
                        ans = max(ans, prev_dp[prev_msk]);
                    } else {
                        ans = min(ans, prev_dp[prev_msk]);
                    }
                }
            }
            nxt_dp[msk] = ans;
        }
        swap(prev_dp, nxt_dp);
    }

    auto ans = accumulate(all(prev_dp), mi(0));
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

