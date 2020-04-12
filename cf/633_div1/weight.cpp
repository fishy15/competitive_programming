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
#define MAXN 100000

using namespace std;

int n;
vector<int> adj[MAXN + 1];
int child[MAXN + 1];
int par[MAXN + 1];
int cnt;

void dfs1(int v, int p) {
    par[v] = par[p] + 1;
    child[v] = 1;

    for (int e : adj[v]) {
        if (e != p) {
            dfs1(e, v);
            child[v] += child[e];
        }
    }
}

void dfs2(int v, int p) {
    if (v != 1) {
        cout << v << ' ' << child[v] << ' ' << n - child[v] << '\n';
        ll val = 1LL * child[v] * (n - child[v]);
        if (val % 2 == 1) {
            cnt++;
        }
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs2(e, v);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    if (cnt == 0) {
        cout << 1 << ' ' << n - 1 << '\n';
    } else if (cnt % 2 == 0) {
        cout << 1 << ' ' << n - 1 - cnt / 2 << '\n';
    } else {
        cout << 3 << ' ' << n - 1 << '\n';
    }

    return 0;
}
