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
#define MAXN 1010

using namespace std;

int n, m;
vector<array<int, 3>> edge1;
vector<array<int, 2>> adj[MAXN][MAXN];
ll dist[MAXN][MAXN];
bool vis[MAXN][MAXN];

void add_edge(int x1, int x2, int y1, int y2) {
    adj[x1][x2].push_back({y1, y2});
    adj[y1][y2].push_back({x1, x2});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; char c; cin >> a >> b >> c;
        a--; b--;
        edge1.push_back({a, b, c});
    }

    for (int i = 0; i < m; i++) {
        for (int j = i; j < m; j++) {
            auto [a, b, c1] = edge1[i];
            auto [u, v, c2] = edge1[j];
            if (c1 != c2) continue;

            add_edge(a, u, b, v);
            add_edge(a, v, b, u);
            add_edge(u, a, v, b);
            add_edge(u, b, v, a);
        }
    }

    memset(dist, 0x3f, sizeof dist);

    queue<array<int, 2>> q;
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        vis[i][i] = true;
        q.push({i, i});
    }

    for (auto [a, b, c] : edge1) {
        for (int i = 0; i < 2; i++) {
            if (vis[a][b]) continue;
            dist[a][b] = 1;
            vis[a][b] = true;
            q.push({a, b});
            swap(a, b);
        }
    }

    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();

        for (auto [x, y] : adj[a][b]) {
            if (!vis[x][y]) {
                dist[x][y] = dist[a][b] + 2;
                vis[x][y] = true;
                q.push({x, y});
            }
        }
    }

    if (!vis[0][n - 1]) {
        cout << "-1\n";
    } else {
        cout << dist[0][n - 1] << '\n';
    }

    return 0;
}
