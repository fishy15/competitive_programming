/*
 * We can form a bipartite graph where we connect a row node to a column node if the value is unknown. We note
 * that if the node has degree zero or one (it is by itself in its row or column), then we will be able to 
 * solve for its value. By solving for it, we can remove it from the graph. However, if there is a cycle, 
 * then we can flip every value and get another valid solution. Therefore, we can determine a solution iff
 * the bipartite graph is a tree. We can compute the maximum spanning tree of the graph and subtract it 
 * from the total cost.
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

void solve() {
    int n; cin >> n;
    vector<vector<int>> a = vector<vector<int>>(n, vector<int>(n));
    vector<vector<int>> b = a;
    vector<int> row(n);
    vector<int> col(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> row[i];
    }

    for (int i =0; i < n; i++) {
        cin >> col[i];
    }

    vector<array<int, 3>> edge;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == -1) {
                edge.push_back({b[i][j], i, n + j});
                ans += b[i][j];
            }
        }
    }

    sort(edge.begin(), edge.end(), greater<>());
    DSU dsu(2 * n);

    for (auto [e, a, b] : edge) {
        if (dsu.find(a) != dsu.find(b)) {
            dsu.join(a, b);
            ans -= e;
        }
    }

    cout << ans << '\n';
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
