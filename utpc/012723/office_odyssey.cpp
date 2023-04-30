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

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(forward<F>(f));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<set<int>> qry(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int t = 0;
    vector up(n, array<int, 20>{});
    vector in(n, 0);
    vector out(n, 0);
    vector d(n, 0);

    auto dfs = y_combinator([&](auto self, int v, int p) -> void {
        in[v] = t++;

        up[v][0] = p;
        for (int i = 1; i < 20; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (auto e : adj[v]) {
            if (e != p) {
                d[e] = d[v] + 1;
                self(e, v);
            }
        }

        out[v] = t++;
    });

    auto anc = [&](int p, int c) {
        return in[p] <= in[c] && out[c] <= out[p];
    };

    auto lca = [&](int x, int y) {
        if (anc(x, y)) return x;
        if (anc(y, x)) return y;

        for (int i = 19; i >= 0; i--) {
            if (!anc(up[x][i], y)) {
                x = up[x][i];
            }
        }

        return up[x][0];
    };

    dfs(0, 0);

    vector cnt(n, 0);
    vector single(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        if (a != b) {
            qry[a].insert(i);
            qry[b].insert(i);

            auto l = lca(a, b);
            cnt[l]++;
        } else {
            single[a]++;
        }
    };

    ll ans = 0;
    auto dfs2 = y_combinator([&](auto self, int v, int p) -> void {
        vector<int> to_rem;
        for (auto e : adj[v]) {
            if (e != p) {
                self(e, v);

                if (qry[v].size() < qry[e].size()) swap(qry[v], qry[e]);
                for (auto x : qry[e]) {
                    if (qry[v].count(x)) {
                        to_rem.push_back(x);
                    } else {
                        qry[v].insert(x);
                    }
                }
            }
        }

        ans += (ll) (single[v] + cnt[v]) * qry[v].size();
        ans += (ll) single[v] * (single[v] - 1) / 2;
        for (auto x : to_rem) qry[v].erase(x);
    });

    dfs2(0, 0);

    for (auto c : cnt) {
        ans -= c + (ll) c * (c - 1) / 2;
    }

    cout << ans << '\n';

    return 0;
}
