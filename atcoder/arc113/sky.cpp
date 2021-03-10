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
#define MAXN 1000000

using namespace std;

ll r, c, k;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}
    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi &operator-=(const mi &m2) {
        v -= m2.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }
};

mi ans;

mi modpow(mi n, ll e) {
    mi res = 1;
    while (e) {
        if (e & 1) res *= n;
        n *= n;
        e >>= 1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> r >> c >> k;

    if (min(r, c) == 1) {
        cout << modpow(k, max(r, c)).v << '\n';
        return 0;
    }

    // i = min(B), max(A) >= i
    for (int i = 1; i <= k; i++) {
        mi b_combo = modpow(i, c);
        if (i > 1) b_combo -= modpow(i - 1, c);
        mi a_combo = modpow(k - i + 1, r);
        b_combo *= a_combo;
        ans += b_combo;
    }

    cout << ans.v << '\n';

    return 0;
}
