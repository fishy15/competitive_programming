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

// change if necessary
#define MAXN 1000000

using namespace std;

int n;
ll grid[510][510];
bool vis[510][510];
ll dist[510][510];

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};

bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n && !vis[x][y];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;

    int px = 0;
    int py = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] > grid[px][py]) {
                px = i;
                py = j;
            }
        }
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, 0, 0});

    while (!pq.empty()) {
        auto [d, x, y] = pq.top();
        pq.pop();
        if (vis[x][y]) continue;

        vis[x][y] = true;
        dist[x][y] = d;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            ll df = abs(grid[x][y] - grid[nx][ny]);
            if (ok(nx, ny)) {
                pq.push({d + df * df, nx, ny});
            }
        }
    }

    cout << dist[px][py] << '\n';

    return 0;
}
