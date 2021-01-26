#include <iostream>
#include <string>
#include <vector>
#include <queue>

#define MAXN 1010

using namespace std;

int n, m, q;
string grid[MAXN];
int dx[4] = {0, -1, 0, 1};
int dy[4] = {1, 0, -1, 0};

bool ok(int x, int y, int n, int m) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

int ff(vector<string> &v, int n, int m) {
    vector<vector<int>> color(n, vector<int>(m));
    int cur = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!color[i][j]) {
                cur++;
                color[i][j] = cur;
                queue<pair<int, int>> q;
                q.push({i, j});

                while (!q.empty()) {
                    auto t = q.front();
                    q.pop();
                    for (int a = 0; a < 4; a++) {
                        int nx = t.first + dx[a];
                        int ny = t.second + dy[a];
                        if (ok(nx, ny, n, m) && !color[nx][ny] && v[i][j] == v[nx][ny]) {
                            color[nx][ny] = cur;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    return cur;
}

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--; b--;

    vector<string> v;
    for (int x = a; x < c; x++) {
        v.push_back(grid[x].substr(b, d - b));
    }

    cout << ff(v, c - a, d - b) << '\n';
}

int main() {
    cin >> n >> m >> q;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    while (q--) {
        solve();
    }

    return 0;
}
