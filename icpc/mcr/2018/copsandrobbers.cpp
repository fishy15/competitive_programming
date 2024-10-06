#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int) (x).size()
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
using vi = vector<int>;
using ll = long long;

constexpr int INF = 0x3f3f3f3f;

template<class T> T edmondsKarp(vector<unordered_map<int, T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vi par(sz(graph)), q = par;

    for (;;) {
        fill(all(par), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        rep(i, 0, ptr) {
            int x = q[i];
            for (auto e : graph[x]) {
                if (par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if (e.first == sink) goto out;
                }
            }
        }
        return flow;
out:
        T inc = numeric_limits<T>::max();
        for (int y = sink; y != source; y = par[y])
            inc = min(inc, graph[par[y]][y]);
        flow += inc;
        for (int y = sink; y != source; y = par[y]) {
            int p = par[y];
            if ((graph[p][y] -= inc) <= 0) graph[p].erase(y);
            graph[y][p] += inc;
        }
    }
}

constexpr array<int, 4> dx = {0, 1, 0, -1};
constexpr array<int, 4> dy = {1, 0, -1, 0};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, c;
    cin >> n >> m>> c;
    swap(n, m); 

    vector<string> grid(n);
    for (auto &row : grid) {
        cin >> row;
    }

    vector<int> costs(c);
    for (auto &x : costs) {
        cin >> x;
    }

    int src = 2 * n * m;
    int sink = 2 * n * m + 1;

    vector<unordered_map<int, ll>> g(2 * n * m + 2);

    auto in = [m](int x, int y) { return 2 * (x * m + y); };
    auto out = [m](int x, int y) { return 2 * (x * m + y) + 1; };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ('a' <= grid[i][j] && grid[i][j] <= 'z') {
                g[in(i, j)][out(i, j)] = costs[grid[i][j] - 'a'];
            } else {
                g[in(i, j)][out(i, j)] = INF;
            }

            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && nj >= 0 && ni < n && nj < m) {
                    g[out(i, j)][in(ni, nj)] = INF;
                }
            }

            if (grid[i][j] == 'B') {
                g[src][in(i, j)] = INF;
            }

            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                g[out(i, j)][sink] = INF;
            }
        }
    }

    auto res = edmondsKarp(g, src, sink);
    if (res >= INF) {
        cout << "-1\n";
    } else {
        cout << res << '\n';
    }

    return 0;
}
