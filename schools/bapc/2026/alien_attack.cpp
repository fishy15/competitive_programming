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

struct BIT {
    int n;
    vector<ll> bit;
    BIT(int n) : n(n), bit(n + 1) {}
    void upd(int x, ll y) {
        x++;
        while (x <= n) {
            bit[x] += y;
            x += x & -x;
        }
    }
    // [0, r)
    ll qry(int r) {
        ll res = 0;
        while (r > 0) {
            res += bit[r];
            r -= r & -r;
        }
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int q;
    cin >> q;

    int qidx = 0;
    vector<array<ll, 5>> queries(q);
    for (auto &cur : queries) {
        cin >> cur[0] >> cur[1] >> cur[2] >> cur[3];
        if (cur[0] == 1) {
            cur[2]--;
        } else {
            cur[2]--;
            cur[3]--;
            cur[4] = qidx;
            qidx++;
        }
    }

    int curt = 0;
    vector<int> in(n), out(n);
    vector up(n, array<int, 20>{});

    auto dfs = [&](auto &&self, int v, int p) -> void {
        in[v] = curt++;
        up[v][0] = p;
        rep(i, 1, 20) {
            up[v][i] = up[up[v][i-1]][i-1];
        }

        for (auto e : adj[v]) {
            if (e != p) {
                self(self, e, v);
            }
        }

        out[v] = curt++;
    };

    auto anc = [&](int a, int b) {
        return in[a] <= in[b] && out[b] <= out[a];
    };

    auto lca = [&](int a, int b) {
        if (anc(a, b)) return a;
        if (anc(b, a)) return b;
        for (int i = 19; i >= 0; i--) {
            if (!anc(up[a][i], b)) {
                a = up[a][i];
            }
        }
        return up[a][0];
    };

    dfs(dfs, 0, 0);

    sort(all(queries), [&](auto &q1, auto &q2) {
        return tie(q1[1], q1[0]) < tie(q2[1], q2[0]);
    });

    vector<ll> ans(qidx);
    BIT energy(2*n);
    BIT active(2*n);
    for (auto &cur : queries) {
        if (cur[0] == 1) {
            auto [typ, t, x, val, _] = cur;
            energy.upd(in[x], val + t);
            energy.upd(out[x], -(val + t));
            active.upd(in[x], 1);
            active.upd(out[x], -1);
        } else {
            auto [typ, t, a, b, i] = cur;

            auto l = lca(a, b);
            auto energy_sum = energy.qry(in[a]+1) + energy.qry(in[b]+1);
            energy_sum -= energy.qry(in[l]+1);
            if (l != 0) {
                energy_sum -= energy.qry(in[up[l][0]]+1);
            }
            auto active_sum = active.qry(in[a]+1) + active.qry(in[b]+1);
            active_sum -= active.qry(in[l]+1);
            if (l != 0) {
                active_sum -= active.qry(in[up[l][0]]+1);
            }

            auto res = energy_sum - active_sum * t;
            ans[i] = res;
        }
    }

    for (auto x : ans) {
        cout << x << '\n';
    }


    return 0;
}
