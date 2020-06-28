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
#define MAXN 200010

using namespace std;

int n, q;
vector<int> adj[MAXN];
int in[MAXN];
int out[MAXN];
int up[MAXN][20];
int t;

void dfs(int v, int p) {
    in[v] = t++;
    up[v][0] = p;

    for (int i = 1; i < 20; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }

    out[v] = t++;
}

bool anc(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

int lca(int a, int b) {
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;
    for (int i = 19; i >= 0; i--) {
        if (!anc(up[a][i], b)) a = up[a][i];
    }
    return up[a][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        x--;
        adj[x].push_back(i);
        adj[i].push_back(x);
    }

    dfs(0, 0);

    while (q--) {
        int x, y; cin >> x >> y;
        x--; y--;
        cout << lca(x, y) + 1 << '\n';
    }

    return 0;
}
