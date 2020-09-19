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

int q;
vector<array<int, 2>> queries;

// original tree
int n, t;
vector<int> adj[MAXN + 1];
int d[MAXN + 1];
int in[MAXN + 1];
int out[MAXN + 1];
int up[MAXN + 1][18];

// centroid decomp
vector<int> roots;
int dist[MAXN + 1];
bool done[MAXN + 1];
vector<int> child[MAXN + 1];
int par[MAXN + 1];

// relevant to problem 
pair<int, int> max_dist[MAXN + 1][2];
bool active[MAXN + 1];

// visited stuff
bool visited[MAXN + 1];

int dfs_sz(int v, int p) {
    dist[v] = 1;

    for (int e : adj[v]) {
        if (e != p && !done[e]) {
            dist[v] += dfs_sz(e, v);
        }
    }

    return dist[v];
}

int find_centroid(int v, int p, int sz) {
    for (int e : adj[v]) {
        if (e != p && !done[e] && 2 * dist[e] > sz) {
            return find_centroid(e, v, sz);
        }
    }

    return v;
}

int build(int v, int p) {
    dfs_sz(v, -1);
    int c = find_centroid(v, -1, dist[v]);
    done[c] = true;
    par[c] = p;

    for (int e : adj[c]) {
        if (!done[e]) {
            int res = build(e, c);
            child[c].push_back(res);
        }
    }

    return c;
}

void dfs(int v, int p) {
    in[v] = t++;
    visited[v] = true;

    up[v][0] = p;
    d[v] = d[p] + 1;

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

int dist_orig(int a, int b) {
    return d[a] + d[b] - 2 * d[lca(a, b)];
}

void add(int v) {
    active[v] = true;
    int cur = v;
    int prev = -1;
    while (cur != -1) {
        int d = dist_orig(v, cur);
        if (d >= max_dist[cur][0].first) {
            max_dist[cur][1] = max_dist[cur][0];
            max_dist[cur][0] = {d, prev}; 
        } else if (d > max_dist[cur][1].first) {
            max_dist[cur][1] = {d, prev};
        }
        prev = cur;
        cur = par[cur];
    }
}

int query(int v) {
    int ans = 0;
    int cur = v;
    int prev = -1;
    while (cur != -1) {
        if (active[cur]) {
            int part = dist_orig(v, cur);
            if (prev == max_dist[cur][0].second) {
                part += max_dist[cur][1].first;
            } else {
                part += max_dist[cur][0].first;
            }
            ans = max(ans, part);
        }

        prev = cur;
        cur = par[cur];
    }

    return ans;
}

int main() {
    ifstream fin("newbarn.in");
    ofstream fout("newbarn.out");

    fin >> q;

    for (int i = 0; i < q; i++) {
        char c; int b; fin >> c >> b;
        if (c == 'B') {
            n++;
            if (b != -1) {
                cout << b << ' ' << n << '\n';
                adj[n].push_back(b);
                adj[b].push_back(n);
            }
            queries.push_back({n, 1});
        } else {
            queries.push_back({b, 0});
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!done[i]) {
            int root = build(i, -1);
            par[root] = -1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, i);
        }
    }

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            cout << dist_orig(i, j) << ' ';
        } cout << '\n';
    }

    for (auto& qq : queries) {
        if (qq[1]) {
            add(qq[0]);
        } else {
            cout << query(qq[0]) << '\n';
            fout << query(qq[0]) << '\n';
        }
    }

    return 0;
}
