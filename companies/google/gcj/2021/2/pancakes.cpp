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
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}
    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        mi m = *this;
        return m *= m2;
    }
    mi pow(int e) {
        mi res = 1;
        mi n = *this;
        while (e) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
    mi inv() {
        return pow(MOD - 2);
    }
};

mi f[MAXN];
mi finv[MAXN];

void precalc() {
    f[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        f[i] = f[i - 1] * i;
    }
    finv[MAXN - 1] = f[MAXN - 1].inv();
    for (int i = MAXN - 2; i >= 0; i--) {
        finv[i] = finv[i + 1] * (i + 1);
    }
}

mi choose(int n, int k) {
    return f[n] * finv[k] * finv[n - k];
}

void solve() {
    int n; cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    function<mi(int,int,int)> solve = [&](int l, int r, int d) -> mi {
        if (l == r) {
            if (nums[l] == d) {
                return 1;
            } else {
                return 0;
            }
        } else {
            int prev = nums[r] - d;
            int sz = r - l + 1;
            if (prev == 0) {
                return solve(l, r - 1, d);
            } else if (prev == sz) {
                return solve(l, r - 1, d + 1);
            } else {
                return solve(l, r - prev - 1, d) * solve(r - prev, r - 1, d + 1) * choose(sz - 1, prev);
            }
        }
    };

    mi res = solve(0, n - 1, 1);
    cout << res.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    precalc();

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
