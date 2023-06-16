/*
 * Suppose that each edge in a group for the query have the same weight. In order to check if this query
 * works, we can simulate Kruskal's algorithm by using whatever edges necessary with a lower weight, then
 * choosing the edges in the query, and then finally greedily picking whatever is needed. Since the final
 * part is guaranteed to finish because the graph is connected, the problem simplifies to checking if 
 * picking the edges in the query causes a cycle in the graph. This can be checked using a persistent DSU
 * structure (add the edges and then roll them all back afterwards).
 *
 * If there are multiple weights in the same query, we can solve for each weight independently. The answer 
 * is yes only if all of the weight groups work for a query.
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
#include <numeric>

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500010

using namespace std;

struct PDSU {
    vector<int> dsu;
    vector<int> rank;
    vector<array<int, 4>> changes;

    PDSU(int n) {
        dsu.resize(n);
        rank.resize(n);
        iota(dsu.begin(), dsu.end(), 0);
        fill(rank.begin(), rank.end(), 1);
    }

    int find(int x) {
        return x == dsu[x] ? x : find(dsu[x]);
    }

    bool join(int x, int y) {
        if ((x = find(x)) != (y = find(y))) {
            if (rank[x] < rank[y]) swap(x, y);
            changes.push_back({y, dsu[y], x, rank[x]});
            dsu[y] = x;
            rank[x] += rank[y];
            return true;
        } else {
            changes.push_back({-1, -1, -1, -1});
            return false;
        }
    }

    void rollback(int n) {
        while (n > 0) {
            auto [y, dy, x, rx] = changes.back();
            changes.pop_back();
            if (y != -1) {
                dsu[y] = dy;
                rank[x] = rx;
            }
            n--;
        }
    }
};

int n, m, q;
vector<array<int, 3>> edges;
vector<pair<int, vector<int>>> groups[MAXN];
vector<int> edge_w[MAXN];
bool ans[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        a--; b--;
        edges.push_back({a, b, w});
        edge_w[w].push_back(i);
    }

    cin >> q;
    fill(ans, ans + q, true);
    for (int i = 0; i < q; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int x; cin >> x;
            x--;

            int w = edges[x][2];
            if (groups[w].empty() || groups[w].back().first != i) {
                groups[w].push_back({i, {}});
            }

            groups[w].back().second.push_back(x);
        }
    }

    PDSU dsu(n);
    for (int i = 0; i < MAXN; i++) {
        // check queries
        for (auto [x, v] : groups[i]) {
            for (int j : v) {
                ans[x] &= dsu.join(edges[j][0], edges[j][1]);
            }
            dsu.rollback(v.size());
        }

        // add edges
        for (auto x : edge_w[i]) {
            dsu.join(edges[x][0], edges[x][1]);
        }
    }

    for (int i = 0; i < q; i++) {
        cout << (ans[i] ? "YES" : "NO") << '\n';
    }

    return 0;
}
