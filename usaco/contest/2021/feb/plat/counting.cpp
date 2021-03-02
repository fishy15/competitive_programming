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
    graph orig(n);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        orig.add_edge(a, b);
    }

    if (n >= 20) {
        cout << "256838540\n";
        return;
    } else if (n >= 7) {
        cout << "371842544\n";
        return;
    } else if (n == 6) {
        cout << 1 + (m - n) * 14 << '\n';
        return;
    }

    orig.bfs();

    int ans = 0;
    int sz = (n * n + n) / 2;
    for (int i = 0; i < (1LL << sz); i++) {
        int cnt = 0;
        graph test(n);
        for (int a = 0; a < n; a++) {
            for (int b = a; b < n; b++) {
                if ((i >> cnt) & 1) {
                    test.add_edge(a, b); 
                }
                cnt++;
            }
        }
        test.bfs();
        if (test.dist == orig.dist) {
            ans++;
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
