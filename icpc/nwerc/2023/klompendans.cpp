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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    int a, b, c, d;
    cin >> a >> b;
    cin >> c >> d;

    array<int, 8> dx1 = {a, b, b, a, -a, -b, -b, -a};
    array<int, 8> dy1 = {b, a, -a, -b, -b, -a, a, b};
    array<int, 8> dx2 = {c, d, d, c, -c, -d, -d, -c};
    array<int, 8> dy2 = {d, c, -c, -d, -d, -c, c, d};

    vector vis(n, vector(n, array<bool, 2>{}));

    queue<array<int, 3>> q;
    vis[0][0][0] = true;
    vis[0][0][1] = true;

    q.push({0, 0, 0});
    q.push({0, 0, 1});

    while (!q.empty()) {
        auto e = q.front();
        auto x = e[0];
        auto y = e[1];
        auto t = e[2];
        q.pop();

        auto process = [&](auto &dx, auto &dy) {
            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (min(nx, ny) >= 0 && max(nx, ny) < n && !vis[nx][ny][t^1]) {
                    vis[nx][ny][t^1] = true;
                    q.push({nx, ny, t^1});
                }
            }
        };

        if (t == 0) {
            process(dx1, dy1);
        } else {
            process(dx2, dy2);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (vis[i][j][0] || vis[i][j][1]) {
                ans++;
            }
        }
    }

    cout << ans << '\n';


    return 0;
}
