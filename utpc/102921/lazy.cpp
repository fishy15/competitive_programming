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
#define MAXN 100010

using namespace std;

int n, m, k;
vector<array<int, 2>> adj[MAXN];
set<int> house;
ll dist[MAXN];
ll tot_d;
ll max_d;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k >> m;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        house.insert(x);
    }

    for (int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
    }

    memset(dist, 0x3f, sizeof dist);

    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (dist[v] < INFLL) continue;
        dist[v] = d;

        if (house.count(v)) {
            tot_d += d;
            max_d = max(max_d, d);
        }

        for (auto [e, c] : adj[v]) {
            if (dist[e] == INFLL) {
                pq.push({d + c, e});
            }
        }
    }

    cout << 2 * tot_d << ' ' << 2 * max_d << '\n';

    return 0;
}
