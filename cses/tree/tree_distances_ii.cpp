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

int n;
vector<int> adj[MAXN];
int d;
int sz[MAXN];
ll cur;
ll ans[MAXN];

void dfs(int v, int p) {
    sz[v] = 1;
    d++;
    cur += d - 1;
    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            sz[v] += sz[e];
        }
    }
    d--;
}

void dfs2(int v, int p) {
    if (v != 0) {
        cur -= sz[v];
        cur += n - sz[v];
    }
    ans[v] = cur;
    for (int e : adj[v]) {
        if (e != p) {
            dfs2(e, v);
        }
    }
    cur += sz[v];
    cur -= n - sz[v];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);
    dfs2(0, -1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
