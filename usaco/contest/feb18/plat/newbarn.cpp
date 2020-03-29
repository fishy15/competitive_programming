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
int q;
vector<array<int, 2>> queries;

vector<int> adj[MAXN + 1];

// centroid decomp
int dist[MAXN + 1];
bool done[MAXN + 1];
int up[MAXN + 1][18];
vector<int> child[MAXN + 1];
int root;

// ancestor
int t;
int up2[MAXN + 1][18];
int in[MAXN + 1];
int out[MAXN + 1];

// lca on original
int t2;
int in2[MAXN + 1];
int out2[MAXN + 1];
int dist2[MAXN + 1];

// current status
bool added[MAXN + 1];
int max_dist[MAXN + 1];

int dfs(int v, int p) {
    dist[v] = 1;

    for (int e : adj[v]) {
        if (e != p && !done[e]) {
            dist[v] += dfs(e, v);
        }
    }

    return dist[v];
}

int dfs2(int v, int p, int sz) {
    int mm = 0;
    for (int e : adj[v]) {
        if (e != p && !done[e]) {
            if (2 * dist[e] >= sz) {
                return dfs2(e, v, sz);
            }
        }
    }

    return v;
}

int decomp(int v) {
    // cout << v << '\n';
    dfs(v, -1);
    int c = dfs2(v, -1, dist[v]);
    // cout << "\t" << c << '\n';
    done[c] = true;

    for (int e : adj[c]) {
        if (!done[e]) {
            // cout << "\t\t" << e << '\n';
            int u = decomp(e);
            child[c].push_back(u);
            up[u][0] = c;
        }
    }

    return c;
}

void dfs3(int v) {
    in[v] = t++;

    for (int l = 1; l < 18; l++) {
        if (up[v][l - 1] != -1) {
            up[v][l] = up[up[v][l - 1]][l - 1];
        } else {
            up[v][l] = -1;
        }
    }

    for (int e : child[v]) {
        dfs3(e);
    }

    out[v] = t++;
}

void dfs4(int v, int p) {
    in2[v] = t2++;

    dist2[v] = dist2[p] + 1;

    up2[v][0] = p;
    for (int l = 1; l < 18; l++) {
        if (up2[v][l - 1] != -1) {
            up2[v][l] = up2[up2[v][l - 1]][l - 1];
        } else {
            up2[v][l] = -1;
        }
    }

    for (int e : adj[v]) {
        if (e != p) {
            dfs4(e, v);
        }
    }

    out2[v] = t2++;
}

bool anc(int p, int c) {
    return in[p] <= in[c] && out[c] <= out[p];
}

bool anc2(int p, int c) {
    return in2[p] <= in2[c] && out2[c] <= out2[p];
}

int lca(int a, int b) {
    if (anc2(a, b)) {
        return a; 
    }

    if (anc2(b, a)) {
        return b;
    }

    for (int l = 17; l >= 0; l--) {
        if (!anc2(up2[b][l], a)) {
            b = up2[b][l];
        }
    }

    return up2[b][0];
}

int dist_orig(int u, int v) {
    int l = lca(u, v);
    return dist2[u] + dist2[v] - 2 * dist2[l];
}

void add(int v) {
    added[v] = true;

    int cur = v;
    while (cur != -1) {
        // cout << cur << ' ' << v << '\n';
        max_dist[cur] = max(max_dist[cur], dist_orig(cur, v));
        cur = up[cur][0];
    }
}

int query(int v) {
    int ans = 0;
    int cur = v;

    while (cur != -1) {
        // cout << cur << '\n';
        if (added[cur]) {
            for (int e : child[cur]) {
                // cout << "m" << dist_orig(v, cur);
                if (!anc(e, v)) {
                    int d = dist_orig(v, cur);
                    if (max_dist[e]) {
                        d += max_dist[e] + 1;
                    }
                    ans = max(ans, d);
                }
            }
        }

        cur = up[cur][0];
    }

    return ans;
}

int main() {
    ifstream fin("newbarn.in");
    ofstream fout("newbarn.out");

    fin >> q;
    for (int i = 0; i < q; i++) {
        char a; int b; fin >> a >> b;
        if (a == 'B') {
            queries.push_back({'B' - 'A', ++n});
            if (b != -1) {
                adj[b].push_back(n);
                adj[n].push_back(b);
            }
        } else {
            queries.push_back({a, b});
        }
    }

    root = decomp(1);
    up[root][0] = -1;
    dfs3(root);
    dfs4(1, 1);
    
   // cout << root << '\n';

    /*
    for (int i = 1; i <= 4; i++) {
        for (int l = 0; l < 4; l++) {
            cout << up[i][l] << ' ';
        } cout << '\n';
    }
    */

    for (auto& qq : queries) {
        if (qq[0] == 'B' - 'A') {
            // cout << "AA";
            add(qq[1]);
        } else {
            for (int i = 1; i <= n; i++) {
                cout << max_dist[i] << ' ';
            } cout << '\n';
            // fout << query(qq[1]) << '\n';
        }
    }

    return 0;
}
