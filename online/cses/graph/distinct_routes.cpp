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
vector<int> adj[MAXN];
int ind;
vector<array<int, 4>> edge;
int level[MAXN];
int cur[MAXN];
vector<int> cc;

bool bfs() {
    for (int i = 0; i < n; i++) {
        level[i] = -1;
        cur[i] = 0;
    }

    queue<pair<int, int>> q;
    q.push({0, 1});

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        if (level[t.first] != -1) continue;
        level[t.first] = t.second;
        for (int e : adj[t.first]) {
            if (level[edge[e][1]] == -1 && edge[e][2] > edge[e][3]) {
                q.push({edge[e][1], t.second + 1});
            }
        }
    }

    return level[n - 1] != -1;
}

int dfs(int v, int mincap) {
    if (mincap == 0) return 0;
    if (v == n - 1) { 
        return mincap; 
    }
    while (cur[v] < adj[v].size()) {
        auto &e = edge[adj[v][cur[v]]];
        int nxt = e[1];
        if ((nxt != n - 1 && level[v] + 1 != level[nxt]) || e[2] == e[3]) {
            cur[v]++;
            continue;
        }
        int rem = dfs(nxt, min(mincap, e[2] - e[3]));
        if (rem == 0) {
            cur[v]++;
            continue;
        }
        e[3] += rem;
        edge[adj[v][cur[v]] ^ 1][3] -= rem;
        cur[v]++;
        return rem;
    }
    return 0;
}

void dfs2(int v) {
    cc.push_back(v + 1);
    if (v == n - 1) return;
    for (int i = 0; i < adj[v].size(); i++) {
        if (edge[adj[v][i]][3] == 1) {
            edge[adj[v][i]][3] = 0;
            dfs2(edge[adj[v][i]][1]);
            break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(ind++);
        edge.push_back({a, b, 1, 0});
        adj[b].push_back(ind++);
        edge.push_back({b, a, 0, 0});
    }

    ll flow = 0;
    while (true) {
        if (!bfs()) break;
        while (int cur = dfs(0, INF)) {
            flow += cur;
        }
    }

    cout << flow << '\n';
    while (flow--) {
        cc = {};
        dfs2(0);
        cout << cc.size() << '\n';
        for (int i : cc) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}
