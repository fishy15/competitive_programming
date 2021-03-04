/*
 * We can try to construct an MST of the graph, and the mininum weight edge needed to make the 2 ends of a 
 * query in the same component is the answer for that query. For each position, we can find the closest
 * building to it. If two components are adjacent to each other, then we can draw an edge between them. 
 * Using DSU as well as maintaining the sets of unresolved queries, we can figure out which queries are 
 * satisfies at each step.
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
#define MAXN 2010
#define MAXB 200010

using namespace std;

int h, w, p, q;
string grid[MAXN];
int closest[MAXN][MAXN];
int dist[MAXN][MAXN];
int loc[MAXB][2];
vector<array<int, 3>> edge;
int ans[MAXB];

int dsu[MAXB];
int sz[MAXB];
set<int> qry[MAXB];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < h && y < w && !closest[x][y] && grid[x][y] != '#';
}

int find(int a) {
    return a == dsu[a] ? a : dsu[a] = find(dsu[a]);
}

void join(int a, int b, int w) {
    if ((a = find(a)) != (b = find(b))) {
        if (sz[a] < sz[b]) swap(a, b);
        dsu[b] = a;
        sz[a] += sz[b];
        if (qry[a].size() < qry[b].size()) swap(qry[a], qry[b]);
        for (auto x : qry[b]) {
            if (qry[a].count(x)) {
                ans[x] = w;
                qry[a].erase(x);
            } else {
                qry[a].insert(x);
            }
        }
        qry[b] = {};
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w >> p >> q;

    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    queue<array<int, 2>> qq;
    memset(ans, -1, sizeof ans);

    for (int i = 1; i <= p; i++) {
        cin >> loc[i][0] >> loc[i][1];
        loc[i][0]--;
        loc[i][1]--;
        closest[loc[i][0]][loc[i][1]] = i;
        qq.push({loc[i][0], loc[i][1]});
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        qry[a].insert(i);
        qry[b].insert(i);
    }

    iota(dsu, dsu + p + 1, 0);
    fill(sz, sz + p + 1, 1);

    while (!qq.empty()) {
        auto [x, y] = qq.front();
        qq.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (ok(nx, ny)) {
                closest[nx][ny] = closest[x][y];
                dist[nx][ny] = dist[x][y] + 1;
                qq.push({nx, ny});
            }
        }
    }

    for (int i = 0; i < h - 1; i++) {
        for (int j = 0; j < w; j++) {
            if (closest[i][j] != closest[i + 1][j]) {
                int a = closest[i][j];
                int b = closest[i + 1][j];
                if (a != 0 && b != 0) {
                    int w = dist[i][j] + dist[i + 1][j];
                    edge.push_back({w, a, b});
                }
            }
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w - 1; j++) {
            if (closest[i][j] != closest[i][j + 1]) {
                int a = closest[i][j];
                int b = closest[i][j + 1];
                if (a != 0 && b != 0) {
                    int w = dist[i][j] + dist[i][j + 1];
                    edge.push_back({w, a, b});
                }
            }
        }
    }

    sort(edge.begin(), edge.end());

    for (auto [w, a, b] : edge) {
        join(a, b, w);
        if (sz[find(1)] == p) break;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
