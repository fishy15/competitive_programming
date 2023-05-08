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

struct dinic {
    struct edge {
        int u, v;
        ll f, c;
        edge(int u, int v, ll c) : u(u), v(v), f{}, c(c) {}
    };

    vector<vector<int>> adj;
    vector<edge> edges;
    vector<int> level, nxt;
    int start, end;

    dinic(int n, int start, int end) : adj(n), level(n), nxt(n), start(start), end(end) {}

    void add_edge(int u, int v, ll c) {
        adj[u].push_back(edges.size());
        edges.push_back({u, v, c});
        adj[v].push_back(edges.size());
        edges.push_back({v, u, 0});
    }

    bool bfs() {
        queue<int> q;
        q.push(start);
        fill(level.begin(), level.end(), -1);
        level[start] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int e : adj[v]) {
                if (edges[e].c - edges[e].f > 0 && level[edges[e].v] == -1) {
                    level[edges[e].v] = level[v] + 1;
                    q.push(edges[e].v);
                }
            }
        }
        return level[end] != -1;
    }

    ll dfs(int v, ll cur) {
        if (!cur) return 0;
        if (v == end) return cur;
        for (int &i = nxt[v]; i < (int) adj[v].size(); i++) {
            int e = adj[v][i];
            if (level[v] + 1 == level[edges[e].v] && edges[e].c - edges[e].f > 0) {
                ll w = dfs(edges[e].v, min(cur, edges[e].c - edges[e].f));
                if (w) {
                    edges[e].f += w;
                    edges[e ^ 1].f -= w;
                    return w;
                }
            }
        }
        return 0;
    }

    ll flow() {
        ll flow = 0;
        while (true) {
            if (!bfs()) break;
            fill(nxt.begin(), nxt.end(), 0);
            while (ll f = dfs(start, INFLL)) flow += f;
        }
        return flow;
    }
};

bool conn(const string &a, const string &b) {
    int n = a.size();

    vector<int> diff;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            diff.push_back(i);
        }
    }

    return diff.size() == 2 && a[diff[0]] == b[diff[1]] && a[diff[1]] == b[diff[0]];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector adj(n, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (conn(s[i], s[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    vector<bool> vis(n);
    vector<bool> color(n);

    auto dfs = y_combinator([&](auto self, int v, bool cur_color) -> void {
        vis[v] = true;
        color[v] = cur_color;

        for (auto e : adj[v]) {
            if (!vis[e]) {
                self(e, !cur_color);
            }
        }
    });

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, true);
        }
    }

    int st = n;
    int t = st + 1;

    dinic d(n + 2, st, t);
    for (int i = 0; i < n; i++) {
        if (color[i]) {
            d.add_edge(st, i, 1);
            for (auto v : adj[i]) {
                d.add_edge(i, v, INF);
            }
        } else {
            d.add_edge(i, t, 1);
        }
    }

    cout << n - d.flow() << '\n';

    return 0;
}
