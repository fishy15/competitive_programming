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
#define MAXN 1000000

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

int n, k;
mi ans[300];
int co[300];
int sz[300];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        int s; cin >> s;
        sz[i] = s;
        for (int j = 0; j < s; j++) {
            int x; cin >> x;
            x--;
            co[x] = i;
        }

        ans[i] = 1;
    }

    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            int tot = sz[i] + sz[j];
            ans[i] += mi(sz[j]) / tot;
            ans[j] += mi(sz[i]) / tot;
        }
    }

    for (int i = 0; i < n; i++) {
        mi a = ans[co[i]];
        cout << a.v << ' ';
    }
    cout << '\n';

    return 0;
}
