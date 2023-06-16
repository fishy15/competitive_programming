/*
 * Note that the shortest path between two fields of different colors must contain a single edge that
 * contains two different colors, so we only need to worry about that. Additionally, we only need to 
 * consider an MST of the graph. If vertices A and B are adjacent and different colors, then if the edge
 * connecting the two is part of the MST, then it will be considered. If the edge is not counted, then 
 * the path from A to B on the MST must use edges that are less than or equal to the weight of the direct
 * edge, and the color must flip somewhere on this path as well. Therefore, the answer will be counted
 * in this case as well. For each parent, we can note the shortest edge that leads to each color and then
 * process the child and the parent when a change occurs.
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

int n, m, k, q;
multiset<int> tot;

struct graph {
    vector<pair<int, int>> adj[MAXN]; 
    vector<array<int, 3>> edge;
    int dsu[MAXN];
    int rank[MAXN];
    int find(int x) {
        if (x == dsu[x]) return x;
        return dsu[x] = find(dsu[x]);
    }
    void join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (rank[x] < rank[y]) swap(x, y);
            dsu[y] = dsu[x];
            rank[x] += rank[y];
        }
    }
} all;

struct tree {
    vector<pair<int, int>> adj[MAXN];
    int par[MAXN];
    int len[MAXN];
    int type[MAXN];
    multiset<pair<int, int>> diff[MAXN];

    void dfs(int v, int p, int w) {
        par[v] = p;
        len[v] = w;
        for (auto e : adj[v]) {
            if (e.first != p) {
                dfs(e.first, v, e.second);
                add_diff(v, type[e.first], e.second);
            }
        }
        int prev = -1;
        for (const auto &p : diff[v]) {
            if (p.first != type[v] && prev != p.first) {
                add_tot(v, p.first);
            }
            prev = p.first;
        }
    }

    void add_diff(int v, int c, int len) {
        diff[v].insert({c, len});
    }

    void rem_diff(int v, int c, int len) {
        diff[v].erase(diff[v].find({c, len}));
    }

    void add_tot(int v, int c) {
        auto it = diff[v].lower_bound({c, 0});
        if (it != diff[v].end() && it->first == c) {
            tot.insert(it->second);
        }
    }

    void rem_tot(int v, int c) {
        auto it = diff[v].lower_bound({c, 0});
        if (it != diff[v].end() && it->first == c) {
            tot.erase(tot.find(it->second)); 
        }
    }

    void change(int v, int c) {
        if (c == type[v]) return;

        // change children
        add_tot(v, type[v]);
        rem_tot(v, c);

        // change parent
        if (par[v] != -1) {
            if (type[v] != type[par[v]]) {
                rem_tot(par[v], type[v]);
            }

            if (c != type[par[v]]) {
                rem_tot(par[v], c);
            }

            rem_diff(par[v], type[v], len[v]);
            add_diff(par[v], c, len[v]);
            
            if (type[v] != type[par[v]]) {
                add_tot(par[v], type[v]);
            }

            if (c != type[par[v]]) {
                add_tot(par[v], c);
            }
        }

        type[v] = c;
    }
} tree;

int main() {
    ifstream fin("grass.in");
    ofstream fout("grass.out");

    fin >> n >> m >> k >> q;

    for (int i = 0; i < m; i++) {
        int a, b, w; fin >> a >> b >> w;
        a--; b--;
        all.adj[a].push_back({b, w});
        all.adj[b].push_back({a, w});
        all.edge.push_back({w, a, b});
    }

    for (int i = 0; i < n; i++) {
        fin >> tree.type[i];
    }

    sort(all.edge.begin(), all.edge.end());

    for (int i = 0; i < n; i++) {
        all.dsu[i] = i;
        all.rank[i] = 1;
    }

    for (const auto &[w, a, b] : all.edge) {
        if (all.find(a) != all.find(b)) {
            all.join(a, b);
            tree.adj[a].push_back({b, w});
            tree.adj[b].push_back({a, w});
        }
    }

    tree.dfs(0, -1, -1);

    for (int i = 0; i < n; i++) tree.adj[i].clear();

    for (int i = 0; i < q; i++) {
        int a, c; fin >> a >> c;
        a--;
        tree.change(a, c);
        fout << *tot.begin() << '\n';
    }

    return 0;
}
