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
#define MAXN 10000

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<vector<int>> radj;

int bfs(vector<vector<int>> &v) {
    vector<bool> vis(n);
    queue<int> q;
    q.push(0);
    int cnt = 0;

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        if (vis[t]) continue;
        vis[t] = true;
        cnt++;

        for (int e : v[t]) {
            if (!vis[e]) q.push(e);
        }
    }

    for (int i = 1; i < n; i++) {
        if (!vis[i]) return i;
    }

    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    adj.resize(n);
    radj.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        radj[y].push_back(x);
    }
    
    int res1 = bfs(adj);
    int res2 = bfs(radj);
    if (res1) {
        cout << "NO\n";
        cout << 1 << ' ' << res1 + 1 << '\n';
    } else if (res2) {
        cout << "NO\n";
        cout << res2 + 1 << ' ' << 1 << '\n';
    } else {
        cout << "YES\n";
    }

    return 0;
}
