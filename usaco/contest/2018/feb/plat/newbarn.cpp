/*
 * We can do centroid decomposition on the final tree and store, at each node, its centroid ancestors 
 * + the distance to ancestor + which subtree it belongs to. When we build a node, we mark that it is 
 * turned on and update the max distance for each centroid ancestor. When we query a node, we check 
 * through the ancestors to see the best possible path. For each node, we store the two longest paths 
 * within its component that are in different subtrees.
 */

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
pair<char, int> qq[MAXN];

vector<int> adj[MAXN];
vector<array<int, 3>> par[MAXN];
array<int, 2> best[MAXN][2];
int sz[MAXN];
bool vis[MAXN];
bool on[MAXN];

int dfs_sz(int v, int p) {
    sz[v] = 1;
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            sz[v] += dfs_sz(e, v);
        }
    }
    return sz[v];
}

int dfs_root(int v, int p, int n) {
    for (int e : adj[v]) {
        if (e != p && !vis[e] && 2 * sz[e] > n) {
            return dfs_root(e, v, n);
        }
    }
    return v;
}

void dfs_anc(int v, int p, int c, int st, int d) {
    par[v].push_back({c, d, st});
    for (int e : adj[v]) {
        if (e != p && !vis[e]) {
            dfs_anc(e, v, c, st, d + 1);
        }
    }
}

void centroid(int v, int p) {
    dfs_sz(v, -1);
    int c = dfs_root(v, -1, sz[v]);
    vis[c] = true;

    for (int e : adj[c]) {
        if (!vis[e]) {
            dfs_anc(e, c, c, e, 1);
        }
    }

    for (int e : adj[c]) {
        if (!vis[e]) {
            centroid(e, c);
        }
    }
}

void activate(int v) {
    on[v] = true;
    for (auto arr : par[v]) {
        int c = arr[0];
        int d = arr[1];
        int st = arr[2];
        if (d > best[c][0][0]) {
            auto old = best[c][0];
            best[c][0] = {d, st};
            if (st != old[1]) {
                best[c][1] = old;
            }
        } else if (d > best[c][1][0] && st != best[c][0][1]) {
            best[c][1] = {d, st};
        }
    }
}

int qry(int v) {
    int ans = best[v][0][0];
    for (auto arr : par[v]) {
        int c = arr[0];
        int d = arr[1];
        int st = arr[2];
        if (on[c]) {
            if (st == best[c][0][1]) {
                ans = max(ans, d + best[c][1][0]);
            } else {
                ans = max(ans, d + best[c][0][0]);
            }
        }
    }
    return ans;
}

int main() {
    ifstream fin("newbarn.in");
    ofstream fout("newbarn.out");

    fin >> q;
    int cur = 0;
    for (int i = 0; i < q; i++) {
        fin >> qq[i].first >> qq[i].second;
        if (qq[i].second != -1) {
            qq[i].second--;
        }
        if (qq[i].first == 'B') {
            if (qq[i].second >= 0) {
                adj[cur].push_back(qq[i].second);
                adj[qq[i].second].push_back(cur);
            }
            cur++;
        }
    }

    n = cur + 1;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            centroid(i, -1);
        }
        best[i][0][1] = -1;
        best[i][1][1] = -1;
    }

    cur = 0;
    for (int i = 0; i < q; i++) {
        if (qq[i].first == 'B') {
            activate(cur);
            cur++;
        } else {
            fout << qry(qq[i].second) << '\n';
        }
    }

    return 0;
}
