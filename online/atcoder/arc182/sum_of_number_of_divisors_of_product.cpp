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

struct M {
    // first 1 << 6 represent a mask of which locations have been selected
    // last one represents a "terminated" state
    const static int n = (1 << 6) + 1;
    mi m[n][n]; 
    M operator*(const M &m2) {
        M res;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int a = 0; a < n; a++) {
                    res[i][j] += m[i][a] * m2[a][j];
                }
            }
        }
        return res;
    }
    mi *operator[](const int x) { return m[x]; }
    const mi *operator[](const int x) const { return m[x]; }
    static M pow(M m, ll e) {
        M res = I();
        while (e > 0) {
            if (e & 1) res = res * m;
            m = m * m;
            e >>= 1;
        }
        return res;
    }
    static M I() {
        M m;
        for (int i = 0; i < n; i++) m[i][i] = 1;
        return m;
    }
};

array<int, 6> primes = {2, 3, 5, 7, 11, 13};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    int m;
    cin >> n >> m;

    M mat;

    // i = original mask
    // j = new indices set by transition
    rep(i, 0, 1 << 6) {
        rep(j, 0, 1 << 6) {
            if ((i & j) == 0) {
                rep(k, 1, m+1) {
                    mi combo = 1;
                    auto div_k = k;
                    // iterate through primes and compute how many ways to pick mask
                    rep(a, 0, 6) {
                        auto p = primes[a];
                        // only need to process prime if it is claimed by this index
                        if (j & (1 << a)) {
                            int cnt = 0;
                            while (div_k % p == 0) {
                                div_k /= p;
                                cnt++;
                            }
                            combo *= cnt;
                        }
                    }
                    mat[i][i|j] += combo;
                }
            }
        }
    }

    int full_mask = (1 << 6) - 1;
    int ended = 1 << 6;

    // if we have a full mask, then we can enter the terminated state
    // if we are in the terminated stated then we must stay in the terminated state
    mat[full_mask][ended] = 1;
    mat[ended][ended] = 1;

    // extra power for final transition to final state
    auto res = M::pow(mat, n + 1);
    mi ans = 0;

    // can start from any mask since we can pick the 0th index
    rep(i, 0, 1 << 6) {
        ans += res[i][ended];
    }

    // remove extra all-terminate case
    ans -= 1;

    cout << ans.v << '\n';

    return 0;
}
