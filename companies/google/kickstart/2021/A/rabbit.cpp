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
#define MAXN 1000000

using namespace std;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void solve() {
    int r, c; cin >> r >> c;
    vector<vector<int>> grid(r, vector<int>(c));
    vector<vector<int>> res(r, vector<int>(c));
    vector<vector<bool>> vis(r, vector<bool>(c));

    priority_queue<array<ll, 3>> pq;

    auto ok = [&](int x, int y) {
        return x >= 0 && y >= 0 && x < r && y < c && !vis[x][y];
    };

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
            pq.push({grid[i][j], i, j});
        }
    }

    int done = 0;
    while (done < r * c) {
        auto [d, i, j] = pq.top();
        pq.pop();
        
        if (vis[i][j]) continue;
        res[i][j] = d;
        vis[i][j] = true;
        done++;

        for (int k = 0; k < 4; k++) {
            int x = i + dx[k];
            int y = j + dy[k];
            if (ok(x, y)) {
                pq.push({d - 1, x, y});
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            ans += res[i][j] - grid[i][j];
        }
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
