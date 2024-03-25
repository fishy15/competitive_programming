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
#define MAXH 1000000

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

mi p[MAXH + 1][21];

void precalc() {
    p[0][0] = 1;
    for (int i = 1; i <= MAXH; i++) {
        p[i][0] = 1;
        for (int j = 1; j <= min(20, i); j++) {
            p[i][j] = p[i][j - 1] * (i - j + 1);
        }
    }
}

void solve() {
    int n, k, d;
    cin >> n >> k >> d;

    vector<bool> present(MAXH + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        present[x] = true;
    }

    vector<mi> combo(MAXH + 1);
    mi ans;
    for (int i = MAXH; i >= 1; i--) {
        int cnt = 0;
        for (int j = i; j <= MAXH; j += i) {
            if (present[j]) {
                cnt++;
            }
            combo[i] -= combo[j];
        }

        combo[i] += p[cnt][k];

        if (i <= d && d % i == 0) {
            ans += combo[i];
        }
    }

    cout << ans.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t;
    cin >> t;

    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
