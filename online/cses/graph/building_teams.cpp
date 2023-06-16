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
int team[MAXN + 1];
vector<int> adj[MAXN + 1];

void dfs(int v, int t) {
    team[v] = t;
    for (int e : adj[v]) {
        if (!team[e]) {
            if (t == 1) dfs(e, 2);
            else dfs(e, 1);
        }
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
        if (!team[i]) {
            dfs(i, 1);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j : adj[i]) {
            if (team[i] == team[j]) {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << team[i] << ' ';
    } cout << '\n';

    return 0;
}
