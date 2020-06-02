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
#define MAXN 1000000

using namespace std;

int vis[8][8];
vector<array<int, 2>> mov = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

inline bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < 8 && y < 8 && !vis[x][y];
}

inline int calc(int x, int y) {
    int cnt = 0;
    for (const auto& d : mov) {
        int dx = d[0] + x;
        int dy = d[1] + y;
        if (ok(dx, dy)) cnt++;
    }
    return cnt;
}

bool dfs(int x, int y, int pos) {
    vis[x][y] = pos;
    vector<array<int, 3>> v;
    for (const auto &d : mov) {
        int dx = d[0] + x;
        int dy = d[1] + y;
        if (ok(dx, dy)) {
            v.push_back({calc(dx, dy), dx, dy});
        }
    }
    if (v.empty() && pos == 64) return true;
    sort(v.begin(), v.end());
    for (const auto &m : v) {
        if (dfs(m[1], m[2], pos + 1)) return true;
    }
    vis[x][y] = 0;
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int x, y; cin >> y >> x;
    x--; y--;
    dfs(x, y, 1);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << vis[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
