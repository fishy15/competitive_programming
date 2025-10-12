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


array dx = {1, 0, -1, 0};
array dy = {0, -1, 0, 1};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int r, c, n;
    cin >> r >> c >> n;

    // d, i, x, y
    priority_queue<array<int, 4>, vector<array<int, 4>>, greater<>> pq;
    vector dist1(r, vector(c, pair{INF, -1}));
    vector dist2(r, vector(c, pair{INF, -1}));
    rep(i, 0, n) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        pq.push({0, i, x, y});
        dist1[x][y] = {0, i};
    }

    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < r && y < c;
    };

    while (!pq.empty()) {
        auto [d, i, x, y] = pq.top();
        pq.pop();
        if (dist1[x][y] != pair{d, i} && dist2[x][y] != pair{d, i}) continue;

        rep(j, 0, 4) {
            auto nx = x + dx[j];
            auto ny = y + dy[j];
            if (ok(nx, ny)) {
                auto new_d = pair{d + 1, i};
                if (new_d < dist1[nx][ny]) {
                    dist2[nx][ny] = dist1[nx][ny];
                    dist1[nx][ny] = new_d;
                    pq.push({d+1, i, nx, ny});
                } else if (new_d < dist2[nx][ny] && dist1[nx][ny].second != i) {
                    dist2[nx][ny] = new_d;
                    pq.push({d+1, i, nx, ny});
                }
            } 
        }
    }

    rep(i, 0, r) {
        rep(j, 0, c) {
            cout << dist1[i][j].second+1 << ' ';
        }
        cout << '\n';
    }
    rep(i, 0, r) {
        rep(j, 0, c) {
            cout << dist2[i][j].second+1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}
