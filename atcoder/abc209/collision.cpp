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
#define MAXN 100010

using namespace std;

int n, q;
vector<int> adj[MAXN];
int dist[MAXN];

void dfs(int v, int p) {
    for (int e : adj[v]) {
        if (e != p) {
            dist[e] = dist[v] + 1;
            dfs(e, v);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 0);

    while (q--) {
        int c, d; cin >> c >> d;
        c--; d--;
        int dd = dist[c] + dist[d]; // we subtract LCA twice, so parity is the same

        if (dd % 2 == 0) {
            cout << "Town\n";
        } else {
            cout << "Road\n";
        }
    }

    return 0;
}
