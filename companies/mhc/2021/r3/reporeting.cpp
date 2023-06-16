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

struct DSU {
    vector<int> dsu;
    vector<int> sz;

    DSU(int n) {
        dsu.resize(n);
        sz.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
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

    int get_sz(int x) {
        return sz[find(x)];
    }
};

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

mi calc(mi sz) {
    return sz * (sz - 1) / 2;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> join(m);
    for (int i = 0; i < m; i++) {
        cin >> join[i][0] >> join[i][1];
        join[i][0]--;
        join[i][1]--;
        if (join[i][0] > join[i][1]) swap(join[i][0], join[i][1]);
    }

    vector<vector<int>> add(n);
    vector<vector<int>> rem(n);
    for (int i = 0; i < m; i++) {
        auto [a, b] = join[i];
        add[a].push_back(i);
        rem[b].push_back(i);
    }

    vector<vector<int>> to_join(m);
    set<int> cur;
    for (int i = 0; i < n - 1; i++) {
        for (int x : add[i]) {
            cur.insert(x);
        }
        for (int x : rem[i]) {
            cur.erase(x);
        }

        if (!cur.empty()) {
            int mm = *cur.begin();
            to_join[mm].push_back(i);
        }
    }

    DSU dsu(n);
    mi tot = calc(n);
    mi prod = 1;
    for (int i = 0; i < m; i++) {
        for (int x : to_join[i]) {
            if (dsu.find(x) != dsu.find(x + 1)) {
                tot -= calc(dsu.get_sz(x));
                tot -= calc(dsu.get_sz(x + 1));
                dsu.join(x, x + 1);
                tot += calc(dsu.get_sz(x));
            }
        }

        prod *= tot;
    }

    cout << prod.v << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
