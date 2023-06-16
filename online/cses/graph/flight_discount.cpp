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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

int n, m;
vector<pair<int, ll>> adj[MAXN];
ll dist[MAXN][2];
bool vis[MAXN][2];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;
    pq.push({0, 0, 0});

    while (!vis[n - 1][1]) {
        auto p = pq.top();
        pq.pop();
        if (vis[p[1]][p[2]]) continue;
        vis[p[1]][p[2]] = true;
        dist[p[1]][p[2]] = p[0];

        for (auto e : adj[p[1]]) {
            if (p[2] == 0) {
                if (!vis[e.first][0]) {
                    pq.push({p[0] + e.second, e.first, 0});
                }
                if (!vis[e.first][1]) {
                    pq.push({p[0] + e.second / 2, e.first, 1});
                }
            } else {
                if (!vis[e.first][1]) {
                    pq.push({p[0] + e.second, e.first, 1});
                }
            }
        }
    }

    cout << dist[n - 1][1] << '\n';

    return 0;
}
