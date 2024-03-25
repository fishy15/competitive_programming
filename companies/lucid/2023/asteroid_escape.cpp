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

struct loc {
    int x;
    int cur_f;
    int dist;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, f;
    cin >> n >> m >> f;

    vector<int> food(n);
    for (auto &x : food) {
        cin >> x;
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
    }

    queue<loc> q;
    vector dist(n, vector(f + 1, INFLL));

    q.push({0, food[0], 0});
    dist[0][food[0]] = 0;

    while (!q.empty()) {
        auto [x, ff, d] = q.front();
        q.pop();
        
        for (auto y : adj[x]) {
            auto nxt_f = min(f, ff + food[y]);
            if (dist[y][nxt_f] == INFLL) {
                dist[y][nxt_f] = d + 1;
                q.push({y, nxt_f, d + 1});
            }
        }
    }

    cout << dist[n - 1][f] << '\n';

    return 0;
}
