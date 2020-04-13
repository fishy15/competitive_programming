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
#define MAXN 5000

using namespace std;

int n, m;
int w;
int q;
vector<int> adj[MAXN + 1];
vector<pair<int, int>> store[MAXN + 1];
bool vis[MAXN + 1];

int dfs(int g, int r, int a) {
    for (int i = 1; i <= n; i++) vis[i] = false;
    queue<pair<int, int>> q;
    priority_queue<pair<int, int>> pq;

    q.push({g, 0});
    ll sz = 0;
    ll cost = 0;
    while (!q.empty()) {
        auto loc = q.front();
        q.pop();
        if (vis[loc.first]) continue;
        vis[loc.first] = true;

        for (auto p : store[loc.first]) {
            sz += p.second;
            cost += 1LL * p.first * p.second;
            pq.push({p.first, p.second});
        }

        while (!pq.empty()) {
            if (sz <= r) break;
            auto p = pq.top();
            pq.pop();
            sz -= p.second;
            cost -= 1LL * p.first * p.second;
            if (sz < r) {
                pq.push({p.first, r - sz});
                cost += 1LL * p.first * (r - sz);
                sz = r;
            } 
        }

        if (sz == r && cost <= a) {
            return loc.second;
        }

        for (int e : adj[loc.first]) {
            if (!vis[e]) {
                q.push({e, loc.second + 1});
            }
        }
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cin >> w;
    for (int i = 0; i < w; i++) {
        int c, k, p; cin >> c >> k >> p;
        store[c].push_back({p, k});
    }

    cin >> q;
    for (int i = 0; i < q; i++) {
        int g, r, a; cin >> g >> r >> a;
        int ans = dfs(g, r, a);
        cout << ans << '\n';
    }

    return 0;
}
