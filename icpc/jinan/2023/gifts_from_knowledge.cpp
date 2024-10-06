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

// change if necessary
#define MAXN 1000000

using namespace std;

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) (x).begin(), (x).end()

void solve() {
    int r, c;
    cin >> r >> c;

    vector grid(r, vector<bool>(c));
    rep(i,0,r) {
        string row;
        cin >> row;
        rep(j,0,c) {
            grid[i][j] = (row[j] == '1');
        }
    }

    vector<vector<int>> adj(r);
    rep(j, 0, c / 2) {
        vector<int> has;
        bool has_double = false;
        rep(i, 0, r) {
            if (grid[i][j] && grid[i][c - j - 1]) {
                has_double = true;
                has.push_back(i);
            } else if (grid[i][j] || grid[i][c - j - 1]) {
                has.push_back(i);
            }
        }

        if (sz(has) > 2 || (has_double && sz(has) > 1)) {
            cout << "0\n";
            return;
        } else if (sz(has) == 2) {
            int u = has[0];
            int v = has[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    vector<bool> vis(r);
    bool invalid = false;
    auto dfs = [&](auto &&self, int v) -> void {
        vis[v] = true;
        for (auto e : adj[v]) {
            bool needs_flip = false;
            rep(j, 0, c) {
                if (grid[v][j] && grid[e][j]) {
                    needs_flip = true;
                }
            }

            if (needs_flip) {
                if (vis[e]) {
                    invalid = true;
                    return;
                } else {
                    reverse(all(grid[e]));
                }
            }

            if (!vis[e]) {
                self(self, e);
            }

            if (invalid) {
                return;
            }
        }
    };

    if (c % 2 == 1) {
        int middle_cnt = 0;
        rep(i, 0, r) {
            if (grid[i][c / 2]) {
                middle_cnt++;
            }
        }

        if (middle_cnt > 1) {
            invalid = true;
        }
    }

    int ans = 1;
    for (int i = 0; i < r; i++) {
        if (!vis[i]) {
            dfs(dfs, i);

            if (invalid) {
                break;
            } else {
                ans *= 2;
                if (ans >= MOD) ans -= MOD;
            }
        }
    }

    if (invalid) {
        cout << "0\n";
    } else {
        cout << ans << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
