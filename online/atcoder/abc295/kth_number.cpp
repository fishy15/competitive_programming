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

// change if necessary
#define MAXN 2010

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

void precomp() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }

    inv_f[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        inv_f[i] = inv_f[i + 1] * (i + 1);
    }
}

mi c(int n, int k) {
    swap(n, k);
    return f[n] * inv_f[k] * inv_f[n - k];
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    precomp();

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> counts(m + 1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        counts[x]++;
    }

    mi ans;

    int less_count = 0;
    for (int i = 1; i <= m; i++) {
        mi cnt;
        for (int j = 0; j <= counts[0]; j++) {
            mi cur_sum = 0;
            if (less_count + j < k && k <= less_count + j + counts[i]) {
                // can be anything
                cout << i << ' ' << j << " 0 " << (c(j, counts[0]) * mi(i).pow(j) * mi(m - i).pow(counts[0] - j)).v << '\n';
                cnt += c(j, counts[0]) * mi(i).pow(j) * mi(m - i).pow(counts[0] - j);
            } else if (less_count < k && k <= less_count + j) {
                int needed = less_count + j - k + 1;
                cur_sum += c(j, counts[0]) * c(needed, j) * mi(i - 1).pow(j - needed);
                cout << i << ' ' << j << " 1 " << cur_sum.v << ' ' << (mi(i).pow(j - needed)).v << ' ' << (mi(m - i).pow(counts[0] - j)).v << '\n';
                cout << needed << '\n';
                cnt += cur_sum * mi(m - i).pow(counts[0] - j);
            }
        }

        cout << i << ' ' << cnt.v << '\n';
        ans += cnt * i;
        less_count += counts[i];
    }

    ans /= mi(m).pow(counts[0]);
    cout << ans.v << '\n';

    return 0;
}
