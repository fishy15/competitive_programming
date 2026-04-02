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
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector dist(n, vector(n, INF));
    rep(i, 0, n) {
        dist[i][i] = 0;
    }
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        ckmin(dist[u][v], w);
        ckmin(dist[v][u], w);
    }

    rep(i, 0, n) {
        rep(k, 0, n) {
            rep(j, 0, n) {
                ckmin(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    rep(i, 1, n) {
        if (dist[0][i] == INF) {
            cout << "-1\n";
        } else {
            cout << dist[0][i] << '\n';
        }
    }

    return 0;
}
