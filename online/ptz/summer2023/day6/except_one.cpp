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

int mod;

struct mi {
    int v;
    mi() : mi(0) {}
    mi(int _v) : v(_v) {
        if (v >= mod) v -= mod;
        if (v < 0) v += mod;
    }
    mi(ll _v) : v(_v % mod) {}

    mi operator+(mi other) const { return mi(v + other.v); }
    mi operator-(mi other) const { return mi(v - other.v); }
    mi operator*(mi other) const { return mi((ll) v * other.v); }
    mi operator/(mi other) const { return *this * other.inv(); }

#define OP(op) \
    mi &operator op##= (mi other) { return *this = *this op other; }

    OP(+); OP(-); OP(*); OP(/);

    mi pow(ll e) const {
        if (v == 0) return 0;
        mi res = 1;
        mi cur = *this;
        while (e) {
            if (e & 1) res *= cur;
            cur *= cur;
            e >>= 1;
        }
        return res;
    }

    mi inv() const {
        return pow(mod - 2);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int p, k, t;
    cin >> p >> k >> t;

    mod = p;

    cout << mi(-k).pow(t).v << '\n';

    return 0;
}
