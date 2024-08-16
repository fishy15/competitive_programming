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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) : dsu(n), sz(n, 1) {
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> ops(q);
    rep(i, 0, q) {
        cin >> ops[i].first >> ops[i].second;
    }

    // 1 = front, 2 = back
    vector<int> orient(q);
    bool ok = true;

    auto set_idx = [&](int i, int v) {
        if (orient[i] == 0) {
            orient[i] = v;
        } else if (orient[i] != v) {
            ok = false;
        }
    };

    rep(i, 0, q) {
        rep(j, i+1, q) {
            auto [p1, v1] = ops[i];
            auto [p2, v2] = ops[j];

            if (v1 > v2) {
                if (p1 < p2) {
                    set_idx(i, 1);
                    set_idx(j, 2);
                } else if (p1 > p2) {
                    set_idx(i, 2);
                    set_idx(j, 1);
                } else {
                    ok = false;
                }
            }
        }
    }

    if (ok) {
        auto free = count(all(orient), 0);
        cout << mi(2).pow(free).v << '\n';
    } else {
        cout << "0\n";
    }

    return 0;
}
