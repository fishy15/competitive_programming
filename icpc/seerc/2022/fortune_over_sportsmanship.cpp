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

    DSU(int n) : dsu(n) {
        iota(dsu.begin(), dsu.end(), 0);
    }

    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (x > y) swap(x, y);
            dsu[y] = x;
            return true;
        }
        return false;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector grid(n, vector<int>(n));
    for (auto &row : grid) {
        for (auto &x : row) {
            cin >> x;
        }
    }

    vector<array<int, 3>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.push_back({grid[i][j], i, j});
        }
    }

    sort(edges.begin(), edges.end(), greater<>());

    DSU dsu(n);
    vector<pair<int, int>> used;
    ll cost = 0;
    for (auto [w, a, b] : edges) {
        if (dsu.join(a, b)) {
            cost += w;
            used.push_back({a, b});
        }
    }

    DSU dsu2(n);

    cout << cost << '\n';
    for (auto [a, b] : used) {
        a = dsu2.find(a);
        b = dsu2.find(b);
        cout << a + 1 << ' ' << b + 1 << '\n';
        dsu2.join(a, b);
    }

    return 0;
}
