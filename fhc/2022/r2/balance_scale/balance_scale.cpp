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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 9000010

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

mi f[MAXN];
mi f_inv[MAXN];

void precalc() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    f_inv[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        f_inv[i] = f_inv[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    if (k < 0 || k > n) return 0;
    return f[n] * f_inv[k] * f_inv[n - k];
}

void solve() {
    int n, k;
    cin >> n >> k;
    k++;
    
    vector<pair<int, int>> batches(n);
    for (int i = 0; i < n; i++) {
        cin >> batches[i].first >> batches[i].second;
    }

    int x = 0; // smaller
    int y = 0; // equal bad
    int z = 0; // bigger
    int ok = batches[0].first; // equal good

    for (int i = 1; i < n; i++) {
        if (batches[i].second < batches[0].second) {
            x += batches[i].first;
        } else if (batches[i].second == batches[0].second) {
            y += batches[i].first;
        } else {
            z += batches[i].first;
        }
    }

    mi prob_leq = c(x + y + ok, k) / c(x + y + z + ok , k);
    mi prob_nlt = mi(1) - (c(x, k) / c(x + y + ok, k));
    mi prob_ok = mi(ok) / mi(ok + y);
    mi ans = prob_leq * prob_nlt * prob_ok;

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    precalc();

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
