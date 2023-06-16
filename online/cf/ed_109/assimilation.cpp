/*
 * By linearity of expectation, E[sum(pt is covered for each pt)] = sum(E[pt is covered] for each pt). 
 * E[pt is covered] is the probability that it is covered. Using complementary counting, we can compute 
 * how many orders result in each point not being covered. Starting from the lowest distance for each point,
 * we can figure out how many options of distances there are for each value. Summing up the probabilities
 * gives us the answer.
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

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int v) : v(v) {}

    mi &operator+=(const mi &m2) {
        v += m2.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }

    mi operator+(const mi &m2) const {
        mi m = *this;
        return m += m2;
    }

    mi &operator-=(const mi &m2) {
        v -= m2.v;
        if (v < 0) v += MOD;
        return *this;
    }

    mi operator-(const mi &m2) const {
        mi m = *this;
        return m -= m2;
    }

    mi &operator*=(const mi &m2) {
        v = (ll) v * m2.v % MOD;
        return *this;
    }

    mi operator*(const mi &m2) const {
        mi m = *this;
        return m *= m2;
    }

    mi pow(ll e) const {
        mi res = 1;
        mi n = *this;
        while (e) {
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

mi no_match(int n, const vector<int> &loc) {
    mi res = 1;
    for (int i = 0; i < n; i++) {
        int opt = loc[i] - i - 1;
        if (opt <= 0) {
            return 0;
        }
        res *= opt;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m; cin >> n >> m;
    vector<vector<int>> dist(m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            dist[j].push_back(x);
        }
    }

    mi invf = 1;
    for (int i = 1; i <= n; i++) {
        invf *= i;
    }
    invf = invf.inv();

    mi ans = 0;
    for (int i = 0; i < m; i++) {
        sort(dist[i].begin(), dist[i].end());
        ans += (mi(1) - no_match(n, dist[i]) * invf); 
    }

    cout << ans.v << '\n';

    return 0;
}
