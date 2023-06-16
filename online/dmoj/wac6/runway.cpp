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
#define MOD  998244353

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

struct mi {
    int v;
    mi() : v(0) {}
    mi(ll v) : v(v % MOD) {}
    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mi operator+(const mi &m2) {
        mi m(v);
        return m += m2;
    }
    mi &operator*=(const mi &m2) {
        v = (ll)v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        mi m(v);
        return m *= m2;
    }
};

int n, k;
string s;
mi cntw[MAXN];
mi cntc[MAXN];
mi totw, totc;
mi pair_sum;
mi ans;

mi sum(ll x) {
    ll res = x * (x + 1) / 2;
    return mi(res);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    cin >> s;

    for (int i = 0; i < n; i++) {
        if (i) cntw[i] += cntw[i - 1];
        if (s[i] == 'W') cntw[i] += 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        if (i != n - 1) cntc[i] += cntc[i + 1];
        if (s[i] == 'C') cntc[i] += 1;
    }

    totw = cntw[n - 1];
    totc = cntc[0];

    for (int i = 0; i <= k - 1; i++) {
        pair_sum += mi(i) * mi(k - 1 - i);
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == 'A') {
            ans += mi(k) * cntw[i] * cntc[i];
            ans += sum(k - 1) * totw * cntc[i];
            ans += sum(k - 1) * cntw[i] * totc;
            ans += pair_sum * totw * totc;
        }
    }

    cout << ans.v << '\n';

    return 0;
}
