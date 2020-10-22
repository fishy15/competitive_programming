/*
 * First, we can compute the distance of each node from 1. To figure out the answer, we can binary search
 * on the tree by checking various centroids. At a given centroid, if the distance is 0, then we know it is
 * the answer. Otherwise, if the (distance from centroid to x) + (distance from 1 to centroid) 
 * = (distance from 1 to x), then the centroid is an ancestor of x, so we can do the s query. The next 
 * centroid we should consider is the centroid whose component contains the next node. If the current centroid
 * is not an ancestor of x, then none of the children's components must contain x, so the parent's component
 * must contain x.
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
#define MAXN 200010

using namespace std;

int n, d;
vector<int> adj[MAXN];
int par[MAXN];
int dd[MAXN];

int sz[MAXN];
int vis[MAXN];

void dfs(int v, int p) {
    for (int e : adj[v]) {
        if (e != p) {
            par[e] = v;
            dd[e] = dd[v] + 1;
            dfs(e, v);
        }
    }
}

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

bool check(int v, int p, int val) {
    if (v == val) return true;
    for (int e : adj[v]) {
        if (e != p && !vis[e] && check(e, v, val)) return true;
    }
    return false;
}

void centroid(int v) {
    dfs_sz(v, v);
    int c = dfs_root(v, v, sz[v]);
    vis[c] = true;

    cout << "d " << c << endl;
    int dist; cin >> dist;

    if (dist == 0) {
        cout << "! " << c << endl;
    } else if (dist + dd[c] == d) {
        cout << "s " << c << endl;
        int nxt; cin >> nxt;
        for (int e : adj[c]) {
            if (!vis[e] && e != par[c]) {
                if (check(e, c, nxt)) {
                    centroid(e);
                }
            }
        }
    } else {
        centroid(par[c]);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cout << "d 1" << endl;
    cin >> d;

    dfs(1, 0);
    centroid(1);

    return 0;
}
