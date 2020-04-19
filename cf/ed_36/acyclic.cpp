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
#include <stack>
#include <cmath>

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 501

using namespace std;

int n, m;
// next, edge index
vector<pair<int, int>> adj[MAXN];
vector<pair<int, int>> radj[MAXN];
vector<pair<int, int>> edge;
vector<int> bad;
pair<int, int> par[MAXN];
int dist[MAXN];
bool vis[MAXN];
int in[MAXN];
int out[MAXN];
int t;

void dfs(int v, int p, int num) {
    vis[v] = true;
    par[v] = {p, num};
    in[v] = t++;

    for (auto p : adj[v]) {
        if (!vis[p.first]) {
            dfs(p.first, v, p.second);
        }
    }

    out[v] = t++;
}

bool ok(int e) {
    vector<int> deg(n + 1);
    for (int i = 0; i < m; i++) {
        if (i != e) {
            deg[edge[i].second]++;
        }
    }

    queue<int> zero;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            zero.push(i);
        }
    }

    while (!zero.empty()) {
        int cur = zero.front();
        zero.pop();
        cnt++;
        for (auto p : adj[cur]) {
            if (p.second != e) {
                deg[p.first]--;
                if (deg[p.first] == 0) {
                    zero.push(p.first);
                }
            }
        }
    }

    return cnt == n;
}

bool anc(int a, int b) {
    return in[a] <= in[b] && out[b] <= out[a];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back({b, i});
        radj[b].push_back({a, i});
        edge.push_back({a, b});
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, 0, -1);
        }
    }

    for (int i = 0; i < m; i++) {
        auto p = edge[i];
        if (anc(p.second, p.first)) {
            bad.push_back(i);
            int cur = p.first;
            while (cur != p.second) {
                bad.push_back(par[cur].second);
                cur = par[cur].first;
            }
            break;
        }
    }

    if (bad.size() == 0) {
        cout << "YES\n";
        return 0;
    }

    for (int i : bad) {
        if (ok(i)) {
            cout << "YES\n";
            return 0;
        }
    }

    cout << "NO\n";

    return 0;
}
