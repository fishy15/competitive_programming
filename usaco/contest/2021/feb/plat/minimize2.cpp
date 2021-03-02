#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

struct graph {
    int n;
    vector<vector<int>> adj;
    vector<array<int, 2>> dist;
    vector<array<bool, 2>> vis;
    graph(int n) : n(n) {
        adj.resize(n);
        dist.assign(n, {-1, -1});
        vis.resize(n);
    }
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void bfs() {
        queue<array<int, 2>> q;
        q.push({0, 0});
        dist[0][0] = 0;
        vis[0][0] = 1;
        while (!q.empty()) {
            auto [pos, par] = q.front();
            q.pop();
            for (auto e : adj[pos]) {
                if (!vis[e][par ^ 1]) {
                    dist[e][par ^ 1] = dist[pos][par] + 1;
                    vis[e][par ^ 1] = true;
                    q.push({e, par ^ 1});
                }
            }
        }
    }
};

void solve() {
    int n, m; cin >> n >> m;
    graph g(n);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        g.add_edge(a, b);
    }

    g.bfs();

    // if no odd cycle
    if (g.dist[0][0] == -1 || g.dist[0][1] == -1) {
        cout << n - 1 << '\n';
        return;
    } else if (n == m) {
        cout << n << '\n';
        return;
    }

    vector<map<int, int>> cnt_diff(n + 2);
    int ans = n - 1;
    for (int i = 0; i < n; i++) {
        auto x = g.dist[i];
        if (x[0] > x[1]) swap(x[0], x[1]);
        cnt_diff[x[0]][x[1] - x[0]]++;
    }

    for (int i = 0; i <= n; i++) {
        // make copies
        auto cur = cnt_diff[i];
        auto nxt = cnt_diff[i + 1];

        for (auto it = cur.rbegin(); it != cur.rend(); it++) {
            auto [diff, cnt] = *it;
            if (cnt) {
                int rem = min(cnt, nxt[diff]);
                cnt -= rem;
                nxt[diff] -= rem;
            }
            if (cnt) {
                int rem = min(cnt, nxt[diff - 2]);
                cnt -= rem;
                nxt[diff] -= rem;
            }
            if (cnt) {
                if (diff == 1) {
                    ans += (cnt + 1) / 2;
                } else {
                    ans += cnt;
                }
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}

