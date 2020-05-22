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
ll ans[MAXN];
bool vis[MAXN];
vector<pair<int, int>> adj[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    pq.push({0, 0});
    int cc = 0;

    while (cc < n) {
        auto cur = pq.top();
        pq.pop();

        if (vis[cur.second]) continue;
        vis[cur.second] = true;
        ans[cur.second] = cur.first;
        cc++;

        for (auto e : adj[cur.second]) {
            if (!vis[e.first]) {
                pq.push({cur.first + e.second, e.first});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    } cout << '\n';

    return 0;
}
