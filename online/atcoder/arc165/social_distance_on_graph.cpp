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

    DSU(int n) : dsu(n), sz(n) {
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

struct twosat : public DSU {
    int n;
    twosat(int n) : DSU(2 * n), n(n) {}

    int pos(int x) { return 2 * x; }
    int neg(int x) { return 2 * x + 1; }

    void xor_(int a, int b) {
        join(a, b ^ 1);
        join(b, a ^ 1);
    }

    bool ok() {
        for (int i = 0; i < n; i++) {
            if (find(pos(i)) == find(neg(i))) {
                return false;
            }
        }
        return true;
    }
};

void setit(pair<int, int> &p, int x) {
    if (x <= p.first) {
        p.second = p.first;
        p.first = x;
    } else if (x <= p.second) {
        p.second = x;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto check = [&](ll m) {
        twosat ts(n);
        for (int u = 0; u < n; u++) {
            for (auto [v, w] : adj[u]) {
                if (w < m) {
                    ts.xor_(ts.pos(u), ts.pos(v));
                }
            }
        }

        return ts.ok();
    };

    ll l = 0;
    ll r = INFLL;
    ll ans = -1;
    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (check(m)) {
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    // min of any adj two
    for (int u = 0; u < n; u++) {
        pair<int, int> e = {INF, INF};
        for (auto [v, w] : adj[u]) {
            setit(e, w);
        }
        ans = min(ans, (ll) e.first + e.second);
    }

    cout << ans << '\n';

    return 0;
}
