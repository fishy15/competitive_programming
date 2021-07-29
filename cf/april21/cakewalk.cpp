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

int h, w;
string grid[5];

array<int, 2> get_closest(int x, int y) {
    queue<array<int, 2>> q;
    q.push({x, y});
    vector<vector<bool>> vis(h, vector<bool>(w));

    while (!q.empty()) {
        auto [a, b] = q.front();
        q.pop();
        if ((a != x || b != y) && grid[a][b] == '*') {
            return {a, b};
        }

        if (b + 1 < w && !vis[a][b + 1]) {
            vis[a][b + 1] = true;
            q.push({a, b + 1});
        }

        if (a + 1 < h && !vis[a + 1][b]) {
            vis[a + 1][b] = true;
            q.push({a + 1, b});
        }
    }

    return {h, w};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    int cnt = 0;
    array<int, 2> cur = {0, 0};

    while (cur != array<int, 2>{h, w}) {
        auto [x, y] = cur;
        if (grid[x][y] == '*') cnt++;
        cur = get_closest(x, y);
    }

    cout << cnt << '\n';

    return 0;
}
