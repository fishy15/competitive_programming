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
#define MAXN 200010

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

int n;
int l[MAXN];
int r[MAXN];
mi prob[MAXN];
mi ans;

// middle index of all 3
void calc(int i) {
     
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> l[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> r[i];
        r[i]++;
    }

    mi sum_e;

    for (int i = 0; i < n - 1; i++) {
        mi denom = mi(r[i] - l[i]) * mi(r[i + 1] - l[i + 1]);

        int both_r = min(r[i], r[i + 1]);
        int both_l = max(l[i], l[i + 1]);

        mi p_same = mi(max(both_r - both_l, 0)) / denom;
        prob[i] = mi(1) - p_same;
        sum_e += prob[i];
    }

    ans = sum_e * 2 + 1;

    return 0;
}
