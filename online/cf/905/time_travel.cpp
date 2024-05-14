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

    int n, t;
    cin >> n >> t;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < t; i++) {
        int m;
        cin >> m;
        
        for (int j = 0; j < m; j++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }
    }

    int k;
    cin >> k;

    vector<int> ord(k);
    for (auto &x : ord) {
        cin >> x;
        x--;
    }

    vector<int> dist(n, INF);
    dist[0] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});

    // count the first move for free
    for (auto [e, at] : adj[0]) {
        if (at == ord[0]) {
            dist[e] = 0;
            pq.push({0, e});
        }
    }

    map<int, queue<int>> times_after;
    for (int i = 1; i < k; i++) {
        times_after[ord[i]].push(i);
    }

    auto erase = [&](int x) {
        auto &q = times_after[x];
        q.pop();
        if (q.empty()) {
            times_after.erase(x);
        }
    };

    int l = 1;

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (dist[v] != d) {
            continue;
        }

        while (l <= d) {
            erase(ord[l++]);
        }

        for (auto [e, at] : adj[v]) {
            if (times_after.count(at)) {
                int nd = times_after[at].front();
                if (nd < dist[e]) {
                    dist[e] = nd;
                    pq.push({nd, e});
                }
            }
        }
    }

    if (dist[n - 1] == INF) {
        cout << "-1\n";
    } else {
        cout << dist[n - 1] + 1 << '\n';
    }

    return 0;
}
