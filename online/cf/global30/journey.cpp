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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

struct DSU {
    vector<int> par;
    vector<int> dsu;
    vector<int> weight;
    vector<int> odd_cnt;
    vector<int> merged_evens;
    DSU(int n, const vector<int> &odd) : par(n, -1), dsu(n), weight(n, INF), odd_cnt(odd), merged_evens(n) {
        iota(all(dsu), 0);
    }
    int find(int x) {
        return x == dsu[x] ? x : dsu[x] = find(dsu[x]);
    }
    void join(int x, int y, int w) {
        if ((x = find(x)) != (y = find(y))) {
            int c = sz(dsu);
            par[x] = c;
            par[y] = c;
            dsu[x] = c;
            dsu[y] = c;
            par.push_back(-1);
            dsu.push_back(c);
            weight.push_back(w);
            merged_evens.push_back((odd_cnt[x] + odd_cnt[y]) / 2);
            odd_cnt.push_back((odd_cnt[x] + odd_cnt[y]) % 2);
        } else {
            weight[x] = min(weight[x], w);
        }
    }
    void post() {
        for (int i = sz(dsu) - 1; i >= 0; i--) {
            if (par[i] != -1) {
                weight[i] = min(weight[i], weight[par[i]]);
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    ll ans = 0;
    vector<int> deg(n);

    vector<array<int, 3>> edges;
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        deg[u]++;
        deg[v]++;
        ans += w;
        edges.push_back({u, v, w});
    }

    vector<int> odd(n);
    rep(i, 0, n) {
        odd[i] = deg[i] % 2;
    }

    DSU dsu(n, odd);
    for (auto [u, v, w] : edges) {
        dsu.join(u, v, w);
    }
    dsu.post();
    rep(i, 0, sz(dsu.dsu)) {
        ans += dsu.merged_evens[i] * dsu.weight[i];
    }
    cout << ans << '\n';
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
