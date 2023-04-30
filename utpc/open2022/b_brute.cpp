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
};

int n, m;
vector<array<int, 3>> edges;
pair<int, int> mm = {INF, 0};

void solve() {
    DSU dsu(n);
    int cost = 0;

    auto e = edges;
    sort(e.begin(), e.end(), [](auto a, auto b) { return a[2] < b[2]; });
    for (auto [a, b, c] : e) {
        if (dsu.find(a) != dsu.find(b)) {
            dsu.join(a, b);
            cost += c;
        }
    }

    if (cost < mm.first) {
        mm = {cost, 1};
    } else if (cost == mm.first) {
        mm.second++; 
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        edges.push_back({a, b, c});
    }

    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            swap(edges[i][2], edges[j][2]);
            solve();
            swap(edges[i][2], edges[j][2]);
        }
    }

    cout << mm.second << '\n';

    return 0;
}
