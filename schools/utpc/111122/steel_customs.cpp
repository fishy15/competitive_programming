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
#define MAXN 1000000

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, f;
    cin >> n >> m >> f;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;
        b--;

        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    vector<array<ll, 2>> dist(n);
    for (int i = 0; i < n; i++) {
        dist[i].fill(INFLL);
    }
    
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, 0, 0});

    dist[0][0] = 0;

    while (!pq.empty()) {
        auto [d, v, x] = pq.top();
        pq.pop();

        if (dist[v][x] == d) {
            for (auto [w, c] : adj[v]) {
                if (d + c < dist[w][x]) {
                    dist[w][x] = d + c;
                    pq.push({d + c, w, x});
                }

                if (x == 0 && d + f < dist[w][1]) {
                    dist[w][1] = d + f;
                    pq.push({d + f, w, 1});
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        auto ans = min(dist[i][0], dist[i][1]);
        if (ans == INFLL) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}
