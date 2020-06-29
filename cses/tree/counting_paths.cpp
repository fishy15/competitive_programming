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

int n, m;
vector<int> adj[MAXN];
int in[MAXN];
int out[MAXN];
int up[MAXN][20];
int val[MAXN];
int t;
int ans[MAXN];

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

void inc(int a, int b) {
    if (anc(a, b)) {
        val[b]++;
        if (a != 0) val[up[a][0]]--;
    } else if (anc(b, a)) {
        val[a]++;
        if (b != 0) val[up[b][0]]--;
    } else {
        val[a]++;
        val[b]++;
        for (int i = 19; i >= 0; i--) {
            if (!anc(up[a][i], b)) a = up[a][i];
        }
        a = up[a][0];
        val[a]--;
        if (a != 0) val[up[a][0]]--;
    }
}

int dfs2(int v, int p) {
    int cur = val[v];
    for (int e : adj[v]) {
        if (e != p) {
            cur += dfs2(e, v);
        }
    }
    ans[v] = cur;
    return cur;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        inc(a, b);
    }

    dfs2(0, -1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
