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
int t[MAXN][MAXN];
char pp[MAXN][MAXN];

struct pos {
    int x, y;
    int type;
    char dir;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    queue<pos> q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                q.push({i, j, -1, 'E'});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                q.push({i, j, 1, 'E'});
            }
        }
    }

    while (!q.empty()) {
        pos p = q.front();
        q.pop();

        if (pp[p.x][p.y]) continue;
        pp[p.x][p.y] = p.dir;
        t[p.x][p.y] = p.type;

        if (p.x > 0 && !pp[p.x - 1][p.y] && grid[p.x - 1][p.y] != '#') {
            q.push({p.x - 1, p.y, p.type, 'U'});
        }

        if (p.x < n - 1 && !pp[p.x + 1][p.y] && grid[p.x + 1][p.y] != '#') {
            q.push({p.x + 1, p.y, p.type, 'D'});
        }

        if (p.y > 0 && !pp[p.x][p.y - 1] && grid[p.x][p.y - 1] != '#') {
            q.push({p.x, p.y - 1, p.type, 'L'});
        }

        if (p.y < m - 1 && !pp[p.x][p.y + 1] && grid[p.x][p.y + 1] != '#') {
            q.push({p.x, p.y + 1, p.type, 'R'});
        }
    }

    int x = -1;
    int y = -1;
    for (int i = 0; i < n; i++) {
        if (t[i][0] == 1) {
            x = i;
            y = 0;
        } else if (t[i][m - 1] == 1) {
            x = i;
            y = m - 1;
        }
    }

    for (int i = 0; i < m; i++) {
        if (t[0][i] == 1) {
            x = 0;
            y = i;
        } else if (t[n - 1][i] == 1) {
            x = n - 1;
            y = i;
        }
    }

    if (x != -1) {
        string ans = "";
        while (pp[x][y] != 'E') {
            ans += pp[x][y];
            if (pp[x][y] == 'U') x++;
            else if (pp[x][y] == 'D') x--;
            else if (pp[x][y] == 'L') y++;
            else if (pp[x][y] == 'R') y--;
        }
        reverse(ans.begin(), ans.end());
        cout << "YES\n";
        cout << ans.size() << '\n';
        cout << ans << '\n';
    } else {
        cout << "NO\n";
    }

    return 0;
}
