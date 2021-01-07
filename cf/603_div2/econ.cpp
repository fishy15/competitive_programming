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
#define MAXN 1010

using namespace std;

int n;
struct tree {
    int n;
    vector<int> adj[2 * MAXN];
    int conn[MAXN];
    int par[2 * MAXN];
    int deg[2 * MAXN];
    int cur[2 * MAXN];
    int all[MAXN][MAXN];

    tree() {
        memset(par, 0, sizeof par);
        memset(deg, 0, sizeof deg);
        memset(cur, 0, sizeof cur);
        memset(all, 0, sizeof all);
    }

    void dfs(int v, int p) {
        par[v] = p;
        for (int e : adj[v]) {
            if (e != p) {
                deg[v]++;
                dfs(e, v);
            }
        }
    }

    void calc_all() {
        for (int i = 0; i < ::n; i++) {
            memcpy(cur, deg, sizeof cur);
            for (int j = i; j < ::n; j++) {
                if (j - i) all[i][j] = all[i][j - 1];
                int pos = conn[j];
                while (pos && cur[pos] == 0) {
                    all[i][j]++;
                    cur[par[pos]]--; 
                    pos = par[pos];
                }
            }
        }
    }
};

tree top, down;
int dp[MAXN];

int ckmax(int &a, int b) {
    return a = max(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    cin >> top.n;
    for (int i = 0; i < top.n - 1; i++) {
        int x; cin >> x; x--;
        top.adj[i + 1].push_back(x);
        top.adj[x].push_back(i + 1);
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x; x--;
        top.conn[i] = x;
    }

    cin >> down.n;
    for (int i = 0; i < down.n - 1; i++) {
        int x; cin >> x; x--;
        down.adj[i + 1].push_back(x);
        down.adj[x].push_back(i + 1);
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x; x--;
        down.conn[i] = x;
    }

    top.dfs(0, -1);
    down.dfs(0, -1);
    top.calc_all();
    down.calc_all();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            int v = max(top.all[j][i], down.all[j][i]);
            if (j) v += dp[j - 1];
            ckmax(dp[i], v);
        }
    }
    
    cout << dp[n - 1] << '\n';

    return 0;
}
