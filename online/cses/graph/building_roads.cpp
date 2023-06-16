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
#define MAXN 1000000

using namespace std;

int n, m;

vector<int> adj[MAXN + 1];
bool vis[MAXN + 1];
int top[MAXN];
int cnt;

void dfs(int i) {
    vis[i] = true;
    for (int e : adj[i]) {
        if (!vis[e]) dfs(e);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
            top[cnt++] = i;
        }
    }

    cout << cnt - 1 << '\n';
    for (int i = 1; i < cnt; i++) {
        cout << top[i - 1] << ' ' << top[i] << '\n';
    }

    return 0;
}
