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
#define MAXN 1000

using namespace std;

int n, m;
string grid[MAXN];
bool vis[MAXN][MAXN];
int cnt;

void dfs(int i, int j) {
    vis[i][j] = true;
    vector<pair<int, int>> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto p : d) {
        int x = i + p.first;
        int y = j + p.second;
        if (x >= 0 && y >= 0 && x < n && y < m && !vis[x][y] && grid[x][y] == '.') {
            dfs(x, y);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && grid[i][j] == '.') {
                cnt++;
                dfs(i, j);
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
