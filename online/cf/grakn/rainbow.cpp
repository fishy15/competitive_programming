/*
 * Construct a bipartite graph of sets and nodes, where an edge exists between a set and node if 
 * that node is in that set. There are no rainbow cycles if there are no cycles in the bipartite graph, 
 * so the minimum cost to remove nodes from set (aka removing edges from bipartite graph) is the cost 
 * needed to remove edges not part of the maximum spanning tree.
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

int n, m;
int a[MAXN];
int b[MAXN];
vector<array<ll, 3>> edge;

ll tot;
ll cost;
int dsu[2 * MAXN];
int sz[2 * MAXN];

int get(int x) {
    if (x == dsu[x]) return x;
    return dsu[x] = get(dsu[x]);
}

void join(int x, int y, ll c) {
    if ((x = get(x)) != (y = get(y))) {
        cost += c;
        if (sz[x] < sz[y]) swap(x, y);
        dsu[y] = x;
        sz[x] += sz[y];
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> m >> n;

    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int i = 0; i < m; i++) {
        int s; cin >> s;
        for (int j = 0; j < s; j++) {
            int x; cin >> x; x--;
            edge.push_back({a[i] + b[x], i, m + x});
            tot += a[i] + b[x];
        }
    }

    for (int i = 0; i < m + n; i++) {
        dsu[i] = i;
        sz[i] = 1;
    }

    sort(edge.rbegin(), edge.rend());

    for (auto &arr : edge) {
        join(arr[1], arr[2], arr[0]); 
    }

    cout << tot - cost << '\n';

    return 0;
}
