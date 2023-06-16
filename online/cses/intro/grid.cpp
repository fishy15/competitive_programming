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
 
string path;
bool vis[7][7];
int row[7];
int col[7];
int cur;
int ans;
 
void dfs(int x, int y) {
    if (x == 6 && y == 0) {
        ans += (cur == 48);
        return;
    } 
 
    vis[x][y] = true;
 
    if (path[cur] == 'L') {
        if (y > 0 && !vis[x][y - 1]) {
            y--;
            cur++;
            dfs(x, y);
            y++;
            cur--;
        }
    } else if (path[cur] == 'R') {
        if (y < 6 && !vis[x][y + 1]) {
            y++;
            cur++;
            dfs(x, y);
            y--;
            cur--;
        }
    } else if (path[cur] == 'U') {
        if (x > 0 && !vis[x - 1][y]) {
            x--;
            cur++;
            dfs(x, y);
            x++;
            cur--;
        }
    } else if (path[cur] == 'D') {
        if (x < 6 && !vis[x + 1][y]) {
            x++;
            cur++;
            dfs(x, y);
            x--;
            cur--;
        }
    } else {
        bool l = y > 0 && !vis[x][y - 1];
        bool r = y < 6 && !vis[x][y + 1];
        bool u = x > 0 && !vis[x - 1][y];
        bool d = x < 6 && !vis[x + 1][y];
        bool bad = (!u && !d && l && r) || (u && d && !l && !r);
        if (l && !bad) {
            y--;
            cur++;
            dfs(x, y);
            y++;
            cur--;
        } 
        if (r && !bad) {
            y++;
            cur++;
            dfs(x, y);
            y--;
            cur--;
        }
        if (u && !bad) {
            x--;
            cur++;
            dfs(x, y);
            x++;
            cur--;
        }
        if (d && !bad) {
            x++;
            cur++;
            dfs(x, y);
            x--;
            cur--;
        }
    }
 
    vis[x][y] = false;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    cin >> path;
    dfs(0, 0);
    cout << ans << '\n';
 
    return 0;
}
