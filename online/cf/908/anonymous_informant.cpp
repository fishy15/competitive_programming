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

struct SCC {
    int sz;
    vector<vector<int>> adj;
    vector<vector<int>> radj;
    vector<int> comp;
    vector<bool> vis;
    vector<int> ord;
    vector<int> cur_comp;

    vector<bool> in_cycle;

    SCC(int m) : sz(m), adj(m), radj(m), comp(m), vis(m), in_cycle(m) {}

    void add_edge(int a, int b) {
        adj[a].push_back(b);
        radj[b].push_back(a);
    }

    void dfs_ord(int v) {
        vis[v] = true;
        for (int e : adj[v]) {
            if (!vis[e]) {
                dfs_ord(e);
            }
        }
        ord.push_back(v);
    }

    void dfs_scc(int v) {
        vis[v] = true;
        cur_comp.push_back(v);
        for (int e : radj[v]) {
            if (!vis[e]) {
                dfs_scc(e);
            }
        }
    }

    void find_scc() {
        for (int i = 0; i < sz; i++) {
            if (!vis[i]) {
                dfs_ord(i);
            }
        }

        fill(vis.begin(), vis.end(), false);
        reverse(ord.begin(), ord.end());

        int cnt = 0;
        for (int v : ord) {
            if (!vis[v]) {
                cur_comp = {};
                dfs_scc(v);
                for (int i : cur_comp) {
                    comp[i] = cnt;
                }
                cnt++;

                auto is_loop = [this](int v) {
                    return find(adj[v].begin(), adj[v].end(), v) != adj[v].end();
                };

                if (cur_comp.size() > 1 || is_loop(cur_comp[0])) {
                    for (auto x : cur_comp) {
                        in_cycle[x] = true;
                    }
                }
            }
        }
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> locs_of(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if (x <= n) {
            locs_of[x].push_back(i);
        }
    }

    SCC scc(n);

    for (int i = 1; i <= n; i++) {
        for (auto idx : locs_of[i]) {
            auto rot_needed = (idx - i + n) % n;
            auto nxt_rot = (rot_needed + i) % n;
            scc.add_edge(rot_needed, nxt_rot);
        }
    }

    scc.find_scc();

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(n, INF);
    dist[0] = k;
    pq.push({k, 0});

    while (!pq.empty()) {
        auto [dd, v] = pq.top();
        pq.pop();

        if (dd != dist[v]) continue;

        if (dd == 0 || scc.in_cycle[v]) {
            cout << "Yes\n";
            return;
        } else {
            for (auto e : scc.radj[v]) {
                auto nd = dd - 1;
                if (nd < dist[e]) {
                    dist[e] = nd;
                    pq.push({nd, e});
                }
            }
        }
    }

    cout << "No\n";
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
