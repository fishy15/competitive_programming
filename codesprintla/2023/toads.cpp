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
#define MAXN 100010

using namespace std;

template<typename F>
struct y_combinator_result {
    F f;
    template<typename T> explicit y_combinator_result(T &&f) : f(std::forward<T>(f)) {}
    template<typename... Args> decltype(auto) operator()(Args &&...args) {
        return f(ref(*this), std::forward<Args>(args)...);
    }
};

template<typename F>
decltype(auto) y_combinator(F &&f) {
    return y_combinator_result<decay_t<F>>(std::forward<F>(f));
}

int n, l;
int edges[MAXN + 10][3];
vector<array<int, 3>> adj[MAXN];
bool tree_edge[MAXN + 10];
int comp[MAXN];
ll depth[MAXN];
ll rel_a[20], rel_b[20];

vector<int> in_cc[MAXN];

vector<int> special[MAXN];
vector<ll> special_dists[MAXN][20];
ll betw_special[MAXN][20][20];

int t;
int in[MAXN];
int out[MAXN];
int up[MAXN][20];

auto dfs(int v, int p, int cc) -> void {
    in[v] = t++;
    up[v][0] = p;
    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    comp[v] = cc;
    in_cc[cc].push_back(v);
    for (auto [e, w, idx] : adj[v]) {
        if (comp[e] == -1) {
            tree_edge[idx] = true;
            depth[e] = depth[v] + w;
            dfs(e, v, cc);
        }
    }

    out[v] = t++;
};

auto anc(int x, int y) {
    return in[x] <= in[y] && out[y] <= out[x];
}

auto lca(int x, int y) {
    if (anc(x, y)) return x;
    if (anc(y, x)) return y;
    for (int i = 19; i >= 0; i--) {
        if (!anc(up[x][i], y)) {
            x = up[x][i];
        }
    }
    return up[x][0];
}

auto tree_dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

int get(int x) {
    int cc = comp[x];
    return lower_bound(in_cc[cc].begin(), in_cc[cc].end(), x) - in_cc[cc].begin();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int j, t;
        cin >> j >> t;
        j--;
        edges[i][0] = i;
        edges[i][1] = j;
        edges[i][2] = t;
    }

    cin >> l;
    for (int i = 0; i < l; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        x--;
        y--;
        edges[i + n][0] = x;
        edges[i + n][1] = y;
        edges[i + n][2] = t;
    }

    for (int i = 0; i < n + l; i++) {
        auto [x, y, t] = edges[i];
        adj[x].push_back({y, t, i});
        adj[y].push_back({x, t, i});
    }

    int num_comps = 0;
    memset(comp, -1, sizeof comp);
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            dfs(i, i, num_comps);
            num_comps++;
        }
    }

    for (int i = 0; i < num_comps; i++) {
        sort(in_cc[i].begin(), in_cc[i].end());
    }

    for (int i = 0; i < n + l; i++) {
        if (!tree_edge[i]) {
            int cc = comp[edges[i][0]];
            special[cc].push_back(edges[i][0]);
            special[cc].push_back(edges[i][1]);
        }
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    auto get_dist = [&](int v) {
        int cc = comp[v];
        vector<ll> d(in_cc[cc].size(), INFLL);

        d[get(v)] = 0;
        pq.push({0, v});

        while (!pq.empty()) {
            auto [dd, v] = pq.top();
            pq.pop();

            for (auto [e, w, _] : adj[v]) {
                auto &val = d[get(e)];
                if (dd + w < val) {
                    val = dd + w;
                    pq.push({val, e});
                }
            }
        }

        return d;
    };

    for (int i = 0; i < num_comps; i++) {
        auto &v = special[i];
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        int sz = v.size();
        for (int j = 0; j < sz; j++) {
            special_dists[i][j] = get_dist(v[j]);
        }

        auto &dd = betw_special[i];
        for (int j = 0; j < sz; j++) {
            for (int k = j + 1; k < sz; k++) {
                ll dist = special_dists[i][j][get(v[k])];
                dd[j][k] = dist;
                dd[k][j] = dist;
            }
        }

        for (int c = 0; c < sz; c++) {
            for (int a = 0; a < sz; a++) {
                for (int b = 0; b < sz; b++) {
                    dd[a][b] = min(dd[a][b], dd[a][c] + dd[c][b]);
                }
            }
        }
    }

    int q;
    cin >> q;

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        if (comp[a] != comp[b]) {
            cout << "-1\n";
        } else {
            ll ans = tree_dist(a, b);
            int cc = comp[a];
            int sz = special[cc].size();

            for (int i = 0; i < sz; i++) {
                rel_a[i] = special_dists[cc][i][get(a)];
                rel_b[i] = special_dists[cc][i][get(b)];
            }

            for (int i = 0; i < sz; i++) {
                for (int j = 0; j < sz; j++) {
                    ans = min(ans, rel_a[i] + betw_special[cc][i][j] + rel_b[j]);
                }
            }

            cout << ans << '\n';
        }
    }

    return 0;
}
