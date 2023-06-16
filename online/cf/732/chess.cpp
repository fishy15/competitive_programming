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
#define MAXN 100010

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
mi inv_f[MAXN];

mi c(int n, int k) {
    return f[n] * inv_f[k] * inv_f[n - k];
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;

    int cnt = 0;
    vector<pair<char, int>> compress;
    for (int i = 0; i < n; i++) {
        if (i > 0 && s[i - 1] != s[i]) {
            compress.push_back({s[i - 1], cnt});
            cnt = 0;
        }

        cnt++;
    }
    compress.push_back({s[n - 1], cnt});

    int sz = compress.size();

    int l = 0;
    mi ans = 1;
    while (l < sz) {
        int zero_cnt = 0;
        int one_cnt = 0;
        int r = l;
        while (r < sz) {
            if (compress[r].first == '1') {
                one_cnt += compress[r].second / 2;
            } else {
                zero_cnt += compress[r].second;
            }
            r++;
        }
        ans *= c(one_cnt + zero_cnt, one_cnt);
        l = r;
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    f[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[100000] = f[100000].inv();
    for (int i = 99999; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
