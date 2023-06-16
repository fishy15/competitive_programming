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
#define MAXN 510

using namespace std;

int h, w;
string grid[MAXN];
bool vis[MAXN][MAXN];
int dist[MAXN][MAXN];

bool ok(int x, int y, int d) {
    return x >= 0 && y >= 0 && x < h && y < w && !vis[x][y] && dist[x][y] > d;
}

int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

int dx2[20] = {-2, -2, -2, -1, -1, -1, -1, -1,  0,  0, 0, 0,  1,  1, 1, 1, 1,  2, 2, 2};
int dy2[20] = {-1,  0,  1, -2, -1,  0,  1,  2, -2, -1, 1, 2, -2, -1, 0, 1, 2, -1, 0, 1}; 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    pq.push({0, 0, 0});

    for (int i = 0; i < h; i++) {
        fill(dist[i], dist[i] + w, INF);
    }

    dist[0][0] = 0;
    while (!pq.empty() && !vis[h - 1][w - 1]) {
        auto [d, x, y] = pq.top();
        pq.pop();

        if (vis[x][y]) continue;
        vis[x][y] = true;

        // go direct
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (ok(nx, ny, d) && grid[nx][ny] == '.') {
                dist[nx][ny] = d;
                pq.push({d, nx, ny});
            }
        }

        // punch
        for (int i = 0; i < 20; i++) {
            int nx = x + dx2[i];
            int ny = y + dy2[i];
            if (ok(nx, ny, d + 1)) {
                dist[nx][ny] = d + 1;
                pq.push({d + 1, nx, ny});
            }
        }
    }

    cout << dist[h - 1][w - 1] << '\n';

    return 0;
}
