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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 500

using namespace std;

int n, m, q;
ll dist[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) dist[i][j] = INFLL;
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b; ll c; cin >> a >> b >> c;
        a--; b--;
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[j][k]);
            }
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if (dist[a][b] == INFLL) {
            cout << -1 << '\n';
        } else {
            cout << dist[a][b] << '\n';
        }
    }

    return 0;
}
