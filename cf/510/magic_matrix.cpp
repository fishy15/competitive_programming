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

struct exp_tracker {
    int n;
    mi sum;
    mi sq_sum;

    exp_tracker() : n(0), sum(), sq_sum() {}

    void add(mi x) {
        sum += x;
        sq_sum += x * x;
        n++;
    }

    mi get_exp() const {
        return sum / n;
    }

    mi get_exp_sq() const {
        return sq_sum / n;
    }

    mi get_exp_of_sq(int d) const {
        //   E[(X - d)^2] 
        // = Var(X - d) + E[X - d]^2
        // = Var(X) + (E[X] - d)^2
        // = E[X^2] - E[X]^2 + (E[X] - d)^2
        
        if (n == 0) return 0;
        
        mi exp = get_exp();
        mi exp_sq = get_exp_sq();

        return exp_sq - (exp * exp) + (exp - d) * (exp - d);
    }
};

int n, m;
int dx, dy;
map<int, vector<array<int, 2>>> locs;
int max_val;
exp_tracker xs, ys, dist;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            locs[x].push_back({i, j});
        }
    }

    cin >> dx >> dy;
    dx--; dy--;

    for (auto &[a, v] : locs) {
        vector<tuple<int, int, mi>> to_add;

        for (auto [x, y] : v) {
            mi exp = xs.get_exp_of_sq(x) + ys.get_exp_of_sq(y) + dist.get_exp();
            to_add.emplace_back(x, y, exp);
        }

        for (auto [x, y, exp] : to_add) {
            if (x == dx && y == dy) {
                cout << exp.v << '\n';
                return 0;
            }

            xs.add(x);
            ys.add(y);
            dist.add(exp);
        }
    }

    return 0;
}
