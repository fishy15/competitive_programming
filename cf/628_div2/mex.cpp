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

vector<pair<int, int>> edge;
vector<int> adj[MAXN + 1];

int val = 1;
int ans[MAXN + 1];
int dist[MAXN + 1];

void dfs(int v, int p) {
    if (v == 1 && adj[v].size() == 1) {
        ans[adj[v][0]] = val++;
    } else if (adj[v].size() == 1) {
        ans[v] = val++;
    }

    if (v > 1) {
        dist[v] = dist[p] + 1;
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;

    if (n == 2) {
        cout << "0\n";
        return 0;
    }
    
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        edge.push_back({a, b});
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 1);

    for (int i = 2; i <= n; i++) {
        if (!ans[i]) {
            ans[i] = val++;
        }
    }

    for (auto p : edge) {
        if (dist[p.first] < dist[p.second]) {
            cout << ans[p.second] - 1 << '\n';
        } else {
            cout << ans[p.first] - 1 << '\n';
        }
    }

    return 0;
}
