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
#include <chrono>
#include <random>

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

    DSU(int n) : dsu(n), sz(n) {
        iota(dsu.begin(), dsu.end(), 0);
        fill(sz.begin(), sz.end(), 1); 
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (sz[x] < sz[y]) swap(x, y);
            dsu[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};

bool triangle(const vector<array<int, 3>> &extra) {
    if (extra.size() != 3) return false;
    set<int> res = {
        extra[0][0], extra[0][1],
        extra[1][0], extra[1][1],
        extra[2][0], extra[2][1],
    };

    return res.size() == 3;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    vector<array<int, 3>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        edges.push_back({u, v, i});
    }

    vector<array<int, 3>> extra;
    do {
        DSU dsu(n);
        extra = {};
        shuffle(edges.begin(), edges.end(), rng);
        for (auto [u, v, idx] : edges) {
            if (!dsu.join(u, v)) {
                extra.push_back({u, v, idx});
            }
        }
    } while (triangle(extra));

    for (int i = 0; i < m; i++) {
        if (count_if(extra.begin(), extra.end(), [i](auto e) { return e[2] == i; })) {
            cout << '1';
        } else {
            cout << '0';
        }
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
