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
#define MAXN 110

using namespace std;

int n, x, k;
int h[MAXN];
ll dist[MAXN][MAXN];
bool vis[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> x >> k;
    x--;

    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (vis[x][y]) continue;
        vis[x][y] = true;
        dist[x][y] = d;

        for (int i = 0; i < n; i++) {
            int diff = max(h[i] - h[x], 0);
            if (!vis[i][y + diff] && y + diff <= k) {
                pq.push({d + dist[x][i], i, y + diff});
            }
        }
    }

    ll ans = INFLL;
    for (int i = 0; i <= k; i++) {
        if (vis[x][i]) {
            ans = min(ans, dist[x][i]);
        }
    }

    if (ans == INFLL) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
