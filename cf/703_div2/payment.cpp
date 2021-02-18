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
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100010

using namespace std;

int n, m;
vector<pair<int, int>> adj[MAXN];
ll dist[MAXN][51][2];
bool vis[MAXN][51][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        a--; b--;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            for (int c = 0; c <= 50; c++) {
                dist[i][c][j] = INFLL;
            }
        }
    }
    dist[0][0][0] = 0;

    // dist, loc, odd/even
    priority_queue<array<ll, 4>, vector<array<ll, 4>>, greater<array<ll, 4>>> pq;
    pq.push({0, 0, 0, 0});

    while (!pq.empty()) {
        auto [d, pw, pos, par] = pq.top();
        pq.pop();
        if (vis[pos][pw][par]) continue;
        vis[pos][pw][par] = true;
        for (auto [e, w] : adj[pos]) {
            pair<ll, ll> nxt = {d + w * w, w};
            if (par == 1) nxt.first += 2 * pw * w;
            if (nxt.first < dist[e][nxt.second][par ^ 1]) {
                dist[e][nxt.second][par ^ 1] = nxt.first;
                pq.push({nxt.first, nxt.second, e, par ^ 1});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        ll mini = INFLL;
        for (int c = 0; c <= 50; c++) {
            mini = min(mini, dist[i][c][0]);
        }
        if (mini == INFLL) {
            cout << "-1 ";
        } else {
            cout << mini << ' ';
        }
    }
    cout << '\n';

    return 0;
}
