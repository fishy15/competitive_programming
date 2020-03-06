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

int n, m;
vector<pair<int, int>> edges;
vector<int> adj[MAXN + 1];
vector<int> add[MAXN + 1];
vector<int> rem[MAXN + 1];

int t;
int in[MAXN + 1];
int out[MAXN + 1];
int up[MAXN + 1][18];

multiset<int> loc[MAXN + 1];
int ans[MAXN + 1];

void dfs(int v, int p) {
    in[v] = t++;

    up[v][0] = p;
    for (int i = 1; i < 18; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
        }
    }

    out[v] = t++;
}

bool anc(int p, int c) {
    return in[p] <= in[c] && out[c] <= out[p];
}

int lca(int a, int b) {
    if (anc(a, b)) return a;
    if (anc(b, a)) return b;

    for (int i = 17; i >= 0; i--) {
        if (!anc(up[b][i], a)) {
            b = up[b][i];
        }
    }

    return up[b][0];
}

void dfs2(int v, int p) {
    for (int a : add[v]) {
        loc[v].insert(a);
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs2(e, v);

            if (loc[e].size() > loc[v].size()) {
                swap(loc[e], loc[v]);
            }

            for (int x : loc[e]) {
                loc[v].insert(x);
            }

            for (auto it = loc[e].begin(); it != loc[e].end(); it++) {
                loc[e].erase(*it);
            }
        }
    }

    for (int r : rem[v]) {
        loc[v].erase(loc[v].find(r));
    }
    
    if (loc[v].empty()) {
        ans[v] = -1;
    } else {
        ans[v] = *loc[v].begin();
    }
}

int main() {
    ifstream fin("disrupt.in");
    ofstream fout("disrupt.out");

    fin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b; fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back({a, b});
    }

    dfs(1, 1);

    for (int i = 0; i < m; i++) {
        int a, b, w; fin >> a >> b >> w;
        if (anc(a, b)) {
            add[b].push_back(w);
            rem[a].push_back(w);
        } else if (anc(b, a)) {
            add[a].push_back(w);
            rem[b].push_back(w);
        } else {
            int p = lca(a, b);
            add[a].push_back(w);
            add[b].push_back(w);
            rem[p].push_back(w);
            rem[p].push_back(w);
        }
    }

    dfs2(1, 1);

    for (int i = 0; i < n - 1; i++) {
        int v = edges[i].second;

        if (anc(edges[i].second, edges[i].first)) {
            v = edges[i].first;
        }

        fout << ans[v] << '\n';
    }

    return 0;
}
