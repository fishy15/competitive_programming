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
#include <functional>
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

int n, m;
vector<array<int, 2>> adj[MAXN];
vector<int> dadj[MAXN];
int deg[MAXN];

int dir[MAXN];
int idx[MAXN];

bool dfs(int v, int d) {
    dir[v] = d;

    for (auto [e, _] : adj[v]) {
        if (dir[e] == 0) {
            dfs(e, 3 - d);
        } else {
            if (dir[e] != 3 - d) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int t, a, b; cin >> t >> a >> b;
        a--; b--;
        adj[a].push_back({b, t});
        adj[b].push_back({a, t});
    }

    for (int i = 0; i < n; i++) {
        if (dir[i] == 0) {
            bool res = dfs(i, 1);
            if (!res) {
                cout << "NO\n";
                return 0;
            }
        }
    }

    for (int a = 0; a < n; a++) {
        for (auto [b, t] : adj[a]) {
            if (a > b) continue; // don't duplicate
            if (dir[a] == t) {
                dadj[a].push_back(b);
                deg[b]++;
            } else {
                dadj[b].push_back(a);
                deg[a]++;
            }
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    int cur = 0;
    while (!q.empty()) {
        int t = q.front(); q.pop();
        for (int e : dadj[t]) {
            deg[e]--;
            if (deg[e] == 0) {
                q.push(e);
            }
        }

        idx[t] = cur;
        cur++;
    }

    if (cur != n) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << (dir[i] == 1 ? 'L' : 'R') << ' ';
        cout << idx[i] << '\n';
    }


    return 0;
}
