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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector adj(n, vector<int>()), radj(n, vector<int>());
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    vector<int> need_close(n);
    rep(i, 0, n) {
        need_close[i] = sz(adj[i]);
    }

    // {# of steps, # of parent steps
    vector dist(n, INF);
    dist[n-1] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, n-1});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (d != dist[v]) continue;

        for (auto e : radj[v]) {
            need_close[e]--;
            auto nd = d + need_close[e] + 1;
            if (nd < dist[e]) {
                dist[e] = nd;
                pq.push({nd, e});
            }
        }
    }

    cout << dist[0] << '\n';

    return 0;
}
