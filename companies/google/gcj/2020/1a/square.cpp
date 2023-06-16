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

void solve() {
    int r, c; cin >> r >> c;
    vector<vector<int>> grid(r);
    vector<vector<int>> up(r);
    vector<vector<int>> down(r);
    vector<vector<int>> left(r);
    vector<vector<int>> right(r);
    vector<vector<bool>> done(r, vector<bool>(c));

    ll sum = 0;
    ll cur = 0;

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int x; cin >> x;
            grid[i].push_back(x);
            up[i].push_back(i - 1);
            down[i].push_back(i + 1);
            left[i].push_back(j - 1);
            right[i].push_back(j + 1);
            cur += x;
        }
    }

    sum = cur;

    vector<pair<int, int>> q;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int cnt = 0;
            ll s = 0;
            if (up[i][j] >= 0) {
                cnt++;
                s += grid[up[i][j]][j];
            }
            if (down[i][j] < r) {
                cnt++;
                s += grid[down[i][j]][j];
            }
            if (left[i][j] >= 0) {
                cnt++;
                s += grid[i][left[i][j]];
            }
            if (right[i][j] < c) {
                cnt++;
                s += grid[i][right[i][j]];
            }

            if (cnt > 0 && s > cnt * grid[i][j]) {
                q.push_back({i, j});
                cur -= grid[i][j];
                done[i][j] = true;
            }
        }
    }

    while (!q.empty()) {
        sum += cur;
        vector<pair<int, int>> tocheck;
        for (auto p : q) {
            if (up[p.first][p.second] >= 0) {
                down[up[p.first][p.second]][p.second] = down[p.first][p.second];
                tocheck.push_back({up[p.first][p.second], p.second});
            }
            if (down[p.first][p.second] < r) {
                up[down[p.first][p.second]][p.second] = up[p.first][p.second];
                tocheck.push_back({down[p.first][p.second], p.second});
            }
            if (left[p.first][p.second] >= 0) {
                right[p.first][left[p.first][p.second]] = right[p.first][p.second];
                tocheck.push_back({p.first, left[p.first][p.second]});
            }
            if (right[p.first][p.second] < c) {
                left[p.first][right[p.first][p.second]] = left[p.first][p.second];
                tocheck.push_back({p.first, right[p.first][p.second]});
            }
        }
        
        q = {};

        for (auto p : tocheck) {
            int i = p.first;
            int j = p.second;
            if (done[i][j]) continue;
            double cnt = 0;
            int s = 0;
            if (up[i][j] >= 0) {
                cnt++;
                s += grid[up[i][j]][j];
            }
            if (down[i][j] < r) {
                cnt++;
                s += grid[down[i][j]][j];
            }
            if (left[i][j] >= 0) {
                cnt++;
                s += grid[i][left[i][j]];
            }
            if (right[i][j] < c) {
                cnt++;
                s += grid[i][right[i][j]];
            }
            if (cnt > 0 && s / cnt - grid[i][j] > eps) {
                q.push_back({i, j});
                cur -= grid[i][j];
                done[i][j] = true;
            }
        }
    }

    cout << sum << '\n';
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
