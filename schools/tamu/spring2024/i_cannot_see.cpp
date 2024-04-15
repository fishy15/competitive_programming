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

using vi = vector<int>;
#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(x) (int) x.size()

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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, c;
    cin >> n >> c;

    vector<int> me(n), them(n);
    for (auto &x : me) {
        cin >> x;
    }
    for (auto &x : them) {
        cin >> x;
    }

    sort(me.begin(), me.end());
    vector<pair<int, int>> me_c;
    for (auto x : me) {
        if (me_c.empty() || me_c.back().first != x) {
            me_c.push_back({x, 1});
        } else {
            me_c.back().second++;
        }
    }

    sort(them.begin(), them.end());
    vector<pair<int, int>> them_c;
    for (auto x : them) {
        if (them_c.empty() || them_c.back().first != x) {
            them_c.push_back({x, 1});
        } else {
            them_c.back().second++;
        }
    }

    set<int> dists;
    for (int d1 : me) {
        for (int d2 : them) {
            dists.insert((d1 + d2) % c);
            dists.insert((d1 - d2 + c) % c);
            dists.insert((-d1 + d2 + c) % c);
            dists.insert((-d1 - d2 + c) % c);
        }
    }

    vector<bool> ok2(them_c.size());
    auto consistent = [&](int loc) {
        int s = me_c.size() + them_c.size();
        int t = s + 1;
        dinic d(me_c.size() + them_c.size() + 2, s, t);
        fill(ok2.begin(), ok2.end(), false);

        int me_c_sz = me_c.size();
        for (int i = 0; i < me_c_sz; i++) {
            auto [x, cnt] = me_c[i];
            d.add_edge(s, i, cnt);

            bool is_set = false;
            int tmp1 = (x - loc + c) % c;
            int they_see1 = min(tmp1, (c - tmp1) % c);
            auto opt_idx1 = lower_bound(them_c.begin(), them_c.end(), pair{they_see1, -1}) - them_c.begin();
            if (them_c[opt_idx1].first == they_see1) {
                d.add_edge(i, me_c_sz + opt_idx1, INF);
                ok2[opt_idx1] = true;
                is_set = true;
            }

            int tmp2 = (x + loc) % c;
            int they_see2 = min(tmp2, (c - tmp2) % c);
            auto opt_idx2 = lower_bound(them_c.begin(), them_c.end(), pair{they_see2, -1}) - them_c.begin();
            if (them_c[opt_idx2].first == they_see2) {
                d.add_edge(i, me_c_sz + opt_idx2, INF);
                ok2[opt_idx2] = true;
                is_set = true;
            }

            if (!is_set) {
                return false;
            }
        }

        for (int i = 0; i < (int) them_c.size(); i++) {
            if (!ok2[i]) return false;
            d.add_edge(me_c_sz + i, t, them_c[i].second);
        }

        return d.flow() == n;
    };

    int ans = 0;
    for (auto x : dists) {
        if (consistent(x)) {
            ans++;
        }
    }

    cout << ans << '\n';

    return 0;
}
