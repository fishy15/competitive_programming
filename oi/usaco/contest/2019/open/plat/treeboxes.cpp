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
#include "grader.h"

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 100000

using namespace std;

int n, q;
vector<int> adj[MAXN];
pair<int, int> loc[MAXN];
int sz[MAXN];

// lca stuff
int t;
int in[MAXN];
int out[MAXN];
int up[MAXN][18];


void dfs(int v, int p) {
    cout << v << ' ' << p << '\n';
    in[v] = t++;

    up[v][0] = p;
    for (int i = 1; i < 18; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }

    sz[v] = 1;

    for (int e : adj[v]) {
        if (e != p) {
            dfs(e, v);
            sz[v] += sz[e];
        }
    }

    out[v] = t++;
}

void dfs2(int v, int p) {
    int curX = loc[v].first;
    int curY = loc[v].second + sz[v];

    for (int e : adj[v]) {
        if (e != p) {
            curX++;
            curY--;
            curY -= sz[e] - 1;
            loc[e].first = curX;
            loc[e].second = curY;
            curX += sz[e] - 1;
            dfs2(e, v);
        }
    }
}
 
bool is_ancestor(int p, int c) {
    return in[p] <= in[c] && out[c] <= out[p];
}

pair<int, int> lca(int a, int b) {
    if (is_ancestor(a, b)) {
        return {a, -1};
    }

    if (is_ancestor(b, a)) {
        return {b, -1};
    }

    for (int i = 17; i >= 0; i--) {
        if (!is_ancestor(up[a][i], b)) {
            a = up[a][i];
        }
    }
    
    return {up[a][0], a};
}
void addRoad(int a, int b) {
	adj[a].push_back(b);
    adj[b].push_back(a);
}

void buildFarms() {
	n = getN();
    q = getQ();
    dfs(0, 0);

    loc[0] = {1, 1};
    dfs2(0, 0);
    for (int i = 0; i < n; i++) {
        setFarmLocation(i, loc[i].first, loc[i].second);
    }
}

void notifyFJ(int a, int b) {
	auto res = lca(a, b);
    if (res.second == -1) {
        int minX = min(loc[a].first, loc[b].first);
        int minY = min(loc[a].second, loc[b].second);
        int maxX = max(loc[a].first, loc[b].first);
        int maxY = max(loc[a].second, loc[b].second);
        addBox(minX, minY, maxX, maxY);
    } else {
        int minX = min(loc[res.first].first, loc[b].first);
        int minY = min(loc[res.first].second, loc[b].second);
        int maxX = max(loc[res.first].first, loc[b].first);
        int maxY = max(loc[res.first].second, loc[b].second);
        addBox(minX, minY, maxX, maxY);
        minX = min(loc[res.second].first, loc[a].first);
        minY = min(loc[res.second].second, loc[a].second);
        maxX = max(loc[res.second].first, loc[a].first);
        maxY = max(loc[res.second].second, loc[a].second);
        addBox(minX, minY, maxX, maxY);
    }
}

/*
int main() {
    N = 7;
    Q = 3;
    addRoad(0, 1);
    addRoad(1, 2);
    addRoad(2, 3);
    addRoad(3, 4);
    addRoad(4, 5);
    addRoad(0, 6);
    buildFarms();
    auto res = lca(4, 6);
    cout << res.first << ' ' << res.second << '\n';
    notifyFJ(5, 6);
    return 0;
}
*/