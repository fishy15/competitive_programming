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
#include <unordered_map>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500010

using namespace std;

int n, q;
vector<int> adj[MAXN];
int val[MAXN];

// 0 = don't pick centroid, 1 = pick centroid
vector<array<ll, 2>> dist[MAXN];
vector<array<int, 2>> c_anc[MAXN];

bool vis[MAXN];
int sz[MAXN];

void dfs_sz(int v, int p) {
    sz[v] = 1;
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            dfs_sz(e, v);
            sz[v] += sz[e];
        }
    }
}

int dfs_c(int v, int p, int tot) {
    for (int e : adj[v]) {
        if (e != p && !vis[e] && 2 * sz[e] > tot) {
            return dfs_c(e, v, tot);
        }
    }

    return v;
}

void dfs_mark(int v, int p, int c, array<ll, 2> p_pick, array<ll, 2> p_no_pick) {
    for (int i = 0; i < 2; i++) {
        ll new_pick = p_no_pick[i] + val[v];
        ll new_no_pick = max(p_pick[i], p_no_pick[i]);

        p_pick[i] = new_pick;
        p_no_pick[i] = new_no_pick;
    }

    int idx = dist[c].size();

    c_anc[v].push_back({c, idx});

    dist[c].emplace_back();
    dist[c][idx][0] = max(p_pick[0], p_no_pick[0]);
    dist[c][idx][1] = max(p_pick[1], p_no_pick[1]);

    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            dfs_mark(e, v, c, p_pick, p_no_pick);
        }
    }
}

void centroid(int v) {
    dfs_sz(v, v);
    v = dfs_c(v, v, sz[v]);
    vis[v] = true;

    array<ll, 2> pick = {0, val[v]};
    array<ll, 2> no_pick = {0, 0};

    dist[v].emplace_back();
    dist[v][0][0] = 0;
    dist[v][0][1] = val[v];
    c_anc[v].push_back({v, 0});

    for (int e : adj[v]) {
        if (!vis[e]) {
            dfs_mark(e, v, v, pick, no_pick);
        }
    }

    for (int e : adj[v]) {
        if (!vis[e]) {
            centroid(e);
        }
    }
}

array<int, 3> get_c(int a, int b) {
    int sz = min(c_anc[a].size(), c_anc[b].size());

    for (int i = 1; i < sz; i++) {
        if (c_anc[a][i][0] != c_anc[b][i][0]) {
            return {c_anc[a][i - 1][0], c_anc[a][i - 1][1], c_anc[b][i - 1][1]};
        }
    }

    return {c_anc[a][sz - 1][0], c_anc[a][sz - 1][1], c_anc[b][sz - 1][1]};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    centroid(0);

    /*
    for (int i = 0; i < n; i++) {
        cout << "comp " << i << ":\n";

        int sz = dist[i].size();
        for (int j = 0; j < sz; j++) {
            cout << j << ' ' << dist[i][j][0] << ' ' << dist[i][j][1] << '\n';
        }
        cout << '\n';
    }

    for (int i = 0; i < n; i++) {
        cout << "anc " << i << ":\n";
        for (auto [c, x] : c_anc[i]) {
            cout << c << ' ' << x << '\n';
        }
        cout << '\n';
    }
    */

    while (q--) {
        int a, b; cin >> a >> b;
        a--; b--;
        auto [c, ai, bi] = get_c(a, b);

        ll no_pick = dist[c][ai][0] + dist[c][bi][0];
        ll pick = dist[c][ai][1] + dist[c][bi][1] - val[c]; // subtract duplicate

        cout << max(no_pick, pick) << '\n';
    }

    return 0;
}
