/*
 * We note that if two indices have the same value and all the values between them are greater, then we can
 * give them values at the same time, so that will save 1 set. Therefore, we want to figure out for every 
 * pair of indices that have the same value, how many times can we set them at the same time. In the worst
 * case, we will have to set N * M^N values. However, if the distance between the two values is D, then 
 * all the D values must be greater than some value X, the endpoints must be equal to X, and then the rest
 * can be any value. Therefore, for every pair of distances, we can find how much we can save and subtract
 * that from the worst case.
 */

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

int n, m;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v % MOD) {}
    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }
    mi operator*(const mi &m2) {
        mi m = *this;
        return m *= m2;
    }
    mi &operator-=(const mi &m2) {
        v -= m2.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mi pow(ll e) {
        mi res = 1;
        mi n = *this;
        while (e) {
            if (e & 1) res *= n;
            n *= n;
            e >>= 1;
        }
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    mi ans = mi(n) * mi(m).pow(n);

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            mi in = mi(m - j).pow(i - 1);
            mi out = mi(m).pow(n - i - 1);
            ans -= in * out * mi(n - i);
        }
    }

    cout << ans.v << '\n';

    return 0;
}
