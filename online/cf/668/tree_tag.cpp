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
#define MAXN 1000000

using namespace std;

vector<vector<int>> adj;
vector<int> dist;

void dfs(int v, int p, int d) {
    dist[v] = d;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v, d + 1);
        }
    }
}

void solve() {
    int n, a, b, da, db;
    cin >> n >> a >> b >> da >> db;
    a--; b--;
    adj = vector<vector<int>>(n);
    dist = vector<int>(n); 

    for (int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    if (2 * da >= db) {
        cout << "Alice\n";
        return;
    }

    dfs(a, -1, 0);
    if (dist[b] <= da) {
        cout << "Alice\n";
        return;
    }

    int maxd = 0;
    int pos = 0;
    for (int i = 0; i < n; i++) {
        if (dist[i] > maxd) {
            maxd = dist[i];
            pos = i;
        }
    }

    dfs(pos, -1, 0);
    maxd = 0;
    for (int i = 0; i < n; i++) {
        maxd = max(maxd, dist[i]);
    }

    if (2 * da >= maxd) {
        cout << "Alice\n";
        return;
    }
    
    cout << "Bob\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
