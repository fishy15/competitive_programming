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
#include <functional>
#include <numeric>

#define ll long long
#define ld double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 1000000

using namespace std;

#define UL(x, y) 2*(x), 2*(y)
#define U(x, y) 2*(x), 2*(y)+1
#define UR(x, y) 2*(x), 2*(y)+2
#define L(x, y) 2*(x)+1, 2*(y)
#define R(x, y) 2*(x)+1, 2*(y)+2
#define DL(x, y) 2*(x)+2, 2*(y)
#define D(x, y) 2*(x)+2, 2*(y)+1
#define DR(x, y) 2*(x)+2, 2*(y)+2

string grid[700];
vector<tuple<int, int, ld>> adj[1410][1410];
ld dist[1410][1410];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int h, w;
    cin >> h >> w;

    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    auto add_edge = [&](int a, int b, int c, int d, ld dd) {
        adj[a][b].push_back({c, d, dd});
        adj[c][d].push_back({a, b, dd});
    };

    auto arc = 2.5 * acos(-1);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'O') {
                add_edge(L(i, j), U(i, j), arc);
                add_edge(U(i, j), R(i, j), arc);
                add_edge(R(i, j), D(i, j), arc);
                add_edge(D(i, j), L(i, j), arc);
            }

            add_edge(UL(i, j), U(i, j), 5);
            add_edge(U(i, j), UR(i, j), 5);
            add_edge(UR(i, j), R(i, j), 5);
            add_edge(R(i, j), DR(i, j), 5);
            add_edge(DR(i, j), D(i, j), 5);
            add_edge(D(i, j), DL(i, j), 5);
            add_edge(DL(i, j), L(i, j), 5);
            add_edge(L(i, j), UL(i, j), 5);
        }
    }

    for (int i = 0; i < 1410; i++) {
        for (int j = 0; j < 1410; j++) {
            dist[i][j] = INF;
        }
    }

    using T = tuple<ld, int, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, UL(0, 0)});
    dist[0][0] = 0;

    while (!pq.empty()) {
        auto [dd, i, j] = pq.top();
        pq.pop();

        for (auto [ex, ey, w] : adj[i][j]) {
            if (dist[ex][ey] > dd + w) {
                dist[ex][ey] = dd + w;
                pq.push({dd + w, ex, ey});
            }
        }
    }

    auto [resx, resy] = pair{DR(h - 1, w - 1)};
    cout << fixed << setprecision(20);
    cout << dist[resx][resy] << '\n';

    return 0;
}
