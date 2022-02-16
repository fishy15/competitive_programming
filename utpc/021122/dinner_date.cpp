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
#define MAXN 1010

using namespace std;

struct edge {
    int two;
    int five;
    ld lg;
    int nxt;

    edge(int t, int f, ld l, int n) : two(t), five(f), lg(l), nxt(n) {}
};

int n, m, k;
vector<edge> adj[MAXN];
ld dist[MAXN][15][15];
bool vis[MAXN][15][15];

int get_cnt(int x, int y) {
    int cnt = 0;
    while (x % y == 0) {
        x /= y;
        cnt++;
    }
    return cnt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        a--; b--;
        int two = get_cnt(w, 2);
        int five = get_cnt(w, 5);
        ld lg = log10(w); 

        adj[a].emplace_back(two, five, lg, b);
        adj[b].emplace_back(two, five, lg, a);
    }

    priority_queue<tuple<ld, int, int, int>, vector<tuple<ld, int, int, int>>, greater<>> pq;
    pq.push({0, 0, 0, 0});

    while (!pq.empty()) {
        auto [d, t, f, v] = pq.top();
        pq.pop();

        if (vis[v][t][f]) continue;
        vis[v][t][f] = true;
        dist[v][t][f] = d;

        for (auto [tt, ff, w, u] : adj[v]) {
            int nt = min(k, t + tt);
            int nf = min(k, f + ff);
            if (!vis[u][nt][nf]) {
                pq.push({d + w, nt, nf, u});
            }
        }
    }

    if (vis[n - 1][k][k]) {
        cout << fixed << setprecision(12) << dist[n - 1][k][k] << '\n';
    } else {
        cout << "-1\n";
    }

    return 0;
}
