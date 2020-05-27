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

int n, m, k;
vector<pair<int, ll>> adj[MAXN];
ll dist[MAXN][10];
int cnt[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;

    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
    }

    priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;
    pq.push({0, 0});

    while (!dist[n - 1][k - 1]) {
        auto p = pq.top();
        pq.pop();
        if (cnt[p[1]] == k) continue;
        dist[p[1]][cnt[p[1]]++] = p[0];

        for (auto e : adj[p[1]]) {
            if (cnt[e.first] < k) {
                pq.push({p[0] + e.second, e.first});
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << dist[n - 1][i] << ' ';
    }
    cout << '\n';


    return 0;
}
