/*
 * We can loop over every single node and ignore the edges that begin at that node. Using this new graph,
 * we can find the distances using O(n^2) Djikstra. We can then test the edges that are connected to the 
 * current node and check if going through that edge flipped improves the path from 1 to n or from n to 1. 
 */

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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x003f3f3f3f3f3f3f

// change if necessary
#define MAXN 210

using namespace std;

int n, m;
vector<array<int, 3>> adj[MAXN];
vector<array<int, 3>> radj[MAXN];
ll adjm[MAXN][MAXN];
ll radjm[MAXN][MAXN];
ll ans = INFLL;

ll dist_1[MAXN];
ll rdist_1[MAXN];
ll dist_n[MAXN];
ll rdist_n[MAXN];
bool vis[MAXN];

void solve(int rem) {
    for (int i = 0; i < n; i++) {
        dist_1[i] = INFLL;
        dist_n[i] = INFLL;
        rdist_1[i] = INFLL;
        rdist_n[i] = INFLL;
    }

    memset(vis, 0, sizeof vis);
    int e = 0;
    dist_1[0] = 0;
    while (e != -1) {
        ll d = dist_1[e];
        vis[e] = true;
        if (e != rem) {
            for (int u = 0; u < n; u++) {
                if (!vis[u] && d + adjm[e][u] < dist_1[u]) {
                    dist_1[u] = d + adjm[e][u];
                }
            }
        }
        e = -1;
        ll min_d = INFLL;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && dist_1[i] < min_d) {
                e = i;
                min_d = dist_1[i];
            }
        }
    }

    memset(vis, 0, sizeof vis);
    e = n - 1;
    rdist_n[n - 1] = 0;
    while (e != -1) {
        ll d = rdist_n[e];
        vis[e] = true;
        for (int u = 0; u < n; u++) {
            if (!vis[u] && d + radjm[e][u] < rdist_n[u] && u != rem) {
                rdist_n[u] = d + radjm[e][u];
            }
        }
        e = -1;
        ll min_d = INFLL;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && rdist_n[i] < min_d) {
                e = i;
                min_d = rdist_n[i];
            }
        }
    }

    memset(vis, 0, sizeof vis);
    e = n - 1;
    dist_n[n - 1] = 0;
    while (e != -1) {
        int d = dist_n[e];
        vis[e] = true;
        if (e != rem) {
            for (int u = 0; u < n; u++) {
                if (!vis[u] && d + adjm[e][u] < dist_n[u]) {
                    dist_n[u] = d + adjm[e][u];
                }
            }
        }
        e = -1;
        ll min_d = INFLL;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && dist_n[i] < min_d) {
                e = i;
                min_d = dist_n[i];
            }
        }
    }

    memset(vis, 0, sizeof vis);
    e = 0;
    rdist_1[0] = 0;
    while (e != -1) {
        ll d = rdist_1[e];
        vis[e] = true;
        for (int u = 0; u < n; u++) {
            if (!vis[u] && d + radjm[e][u] < rdist_1[u] && u != rem) {
                rdist_1[u] = d + radjm[e][u];
            }
        }
        e = -1;
        ll min_d = INFLL;
        for (int i = 0; i < n; i++) {
            if (!vis[i] && rdist_1[i] < min_d) {
                e = i;
                min_d = rdist_1[i];
            }
        }
    }

    ans = min(ans, dist_1[n - 1] + dist_n[0]);
    if (rem == n || adj[rem].empty()) return;

    // path without flipping
    pair<ll, ll> max_to_n = {dist_1[n - 1], dist_1[n - 1]};
    pair<ll, ll> max_to_1 = {dist_n[0], dist_n[0]};
    pair<ll, ll> r_max_to_1 = {rdist_1[rem], rdist_1[rem]};
    pair<ll, ll> r_max_to_n = {rdist_n[rem], rdist_n[rem]};

    for (const auto &e : adj[rem]) {
        ll to_n = dist_1[rem] + e[1] + rdist_n[e[0]];
        ll to_1 = dist_n[rem] + e[1] + rdist_1[e[0]];

        if (to_n <= max_to_n.first) {
            max_to_n.second = max_to_n.first;
            max_to_n.first = to_n;
        } else if (to_n < max_to_n.second) {
            max_to_n.second = to_n;
        }

        if (to_1 <= max_to_1.first) {
            max_to_1.second = max_to_1.first;
            max_to_1.first = to_1;
        } else if (to_1 < max_to_1.second) {
            max_to_1.second = to_1;
        }

        // no flip best prev path
        ll r_to_n = e[1] + rdist_n[e[0]];
        ll r_to_1 = e[1] + rdist_1[e[0]];

        if (r_to_n <= r_max_to_n.first) {
            r_max_to_n.second = r_max_to_n.first;
            r_max_to_n.first = r_to_n;
        } else if (r_to_n < r_max_to_n.second) {
            r_max_to_n.second = r_to_n;
        }

        if (r_to_1 <= r_max_to_1.first) {
            r_max_to_1.second = r_max_to_1.first;
            r_max_to_1.first = r_to_1;
        } else if (r_to_1 < r_max_to_1.second) {
            r_max_to_1.second = r_to_1;
        }
    }

    // consider flipping this
    for (const auto &e : adj[rem]) {
        ll to_n = dist_1[rem] + e[1] + rdist_n[e[0]];
        ll r_to_n = e[1] + rdist_n[e[0]];
        if (to_n == max_to_n.first) {
            to_n = max_to_n.second;
        } else {
            to_n = max_to_n.first;
        }
        if (r_to_n == r_max_to_n.first) {
            r_to_n = r_max_to_n.second;
        } else {
            r_to_n = r_max_to_n.first;
        }
        to_n = min(to_n, dist_1[e[0]] + e[1] + r_to_n);

        ll to_1 = dist_n[rem] + e[1] + rdist_1[e[0]];
        ll r_to_1 = e[1] + rdist_1[e[0]];
        if (to_1 == max_to_1.first) {
            to_1 = max_to_1.second;
        } else {
            to_1 = max_to_1.first;
        }
        if (r_to_1 == r_max_to_1.first) {
            r_to_1 = r_max_to_1.second;
        } else {
            r_to_1 = r_max_to_1.first;
        }
        to_1 = min(to_1, dist_n[e[0]] + e[1] + r_to_1);

        ans = min(ans, to_n + to_1 + e[2]);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adjm[i][j] = INFLL;
            radjm[i][j] = INFLL;
        }
    }

    for (int i = 0; i < m; i++) {
        int u, v, c, d; cin >> u >> v >> c >> d;
        u--; v--;
        adj[u].push_back({v, c, d});
        radj[v].push_back({u, c, d});
        adjm[u][v] = min(adjm[u][v], (ll)c);
        radjm[v][u] = min(radjm[v][u], (ll)c);
    }

    for (int i = 0; i <= n; i++) {
        solve(i);
    }

    if (ans == INFLL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
