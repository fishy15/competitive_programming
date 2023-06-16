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
vector<int> sz[2];
vector<int> up[20];

void dfs(int v, int p, int a, int b) {
    sz[0][v] = 1;
    sz[1][v] = 1;

    up[0][v] = p;
    for (int i = 1; i < 20; i++) {
        if (up[i - 1][v] != -1) up[i][v] = up[i - 1][up[i - 1][v]];
        else up[i][v] = -1;
    }

    for (int e : adj[v]) {
        dfs(e, v, a, b);
    }

    int cur = v;
    for (int i = 0; i < 20; i++) {
        if (((1 << i) & a) && cur != -1) cur = up[i][cur];
    }
    if (cur != -1) sz[0][cur] += sz[0][v];
    
    cur = v;
    for (int i = 0; i < 20; i++) {
        if (((1 << i) & b) && cur != -1) cur = up[i][cur];
    }
    if (cur != -1) sz[1][cur] += sz[1][v];
}

void solve() {
    int n, a, b; cin >> n >> a >> b;
    adj = {};
    sz[0] = {};
    sz[1] = {};
    adj.resize(n);
    sz[0].resize(n);
    sz[1].resize(n);
    for (int i = 0; i < 20; i++) {
        up[i] = {};
        up[i].resize(n);
    }

    for (int i = 0; i < n - 1; i++) {
        int x; cin >> x;
        x--;
        adj[x].push_back(i + 1);
    }


    dfs(0, -1, a, b);
    ld ans = 0;
    for (int i = 0; i < n; i++) {
        ld p1 = (ld)(sz[0][i]) / n;
        ld p2 = (ld)(sz[1][i]) / n;
        ans += 1 - (1 - p1) * (1 - p2);
    }

    cout << ans << '\n';
}

int main() {
    /* cin.tie(0)->sync_with_stdio(0); */

    int t; cin >> t;
    cout << fixed << setprecision(12);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
