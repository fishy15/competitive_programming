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

struct pos {
    int x, y;
    char dir;
    pos(int x, int y, char d) : x{x}, y{y}, dir{d} {}
};

int n, m;
int ax, ay;
int bx, by;
string grid[MAXN];
char path[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                ax = i;
                ay = j;
            } else if (grid[i][j] == 'B') {
                bx = i;
                by = j;
            }
        }
    }

    queue<pos> q;
    q.push({ax, ay, 'S'});

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (path[p.x][p.y]) continue;
        path[p.x][p.y] = p.dir;

        if (p.x > 0 && grid[p.x - 1][p.y] != '#' && !path[p.x - 1][p.y]) {
            q.push({p.x - 1, p.y, 'U'});
        }

        if (p.x < n - 1 && grid[p.x + 1][p.y] != '#' && !path[p.x + 1][p.y]) {
            q.push({p.x + 1, p.y, 'D'});
        }

        if (p.y > 0 && grid[p.x][p.y - 1] != '#' && !path[p.x][p.y - 1]) {
            q.push({p.x, p.y - 1, 'L'});
        }

        if (p.y < m - 1 && grid[p.x][p.y + 1] != '#' && !path[p.x][p.y + 1]) {
            q.push({p.x, p.y + 1, 'R'});
        }
    }

    if (path[bx][by]) {
        string ans = "";
        while (path[bx][by] != 'S') {
            ans += path[bx][by];
            if (path[bx][by] == 'U') bx++;
            else if (path[bx][by] == 'D') bx--;
            else if (path[bx][by] == 'L') by++;
            else if (path[bx][by] == 'R') by--;
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
