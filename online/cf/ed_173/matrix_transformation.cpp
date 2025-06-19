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

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;

bool works(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    int n = sz(a);
    int m = sz(a[0]);

    vector<pair<int, int>> row_cnt(n), col_cnt(m);
    vector vis_row(n, false), vis_col(m, false);

    queue<pair<int, bool>> q;
    rep(i, 0, n) {
        int cnt = 0;
        rep(j, 0, m) {
            cnt += b[i][j];
        }
        row_cnt[i] = {cnt, m};
        if (cnt == 0) {
            vis_row[i] = true;
            q.push({i, false});
        }
    }
    rep(j, 0, m) {
        int cnt = 0;
        rep(i, 0, n) {
            cnt += b[i][j];
        }
        col_cnt[j] = {cnt, n};
        if (cnt == n) {
            vis_col[j] = true;
            q.push({j, true});
        }
    }

    while (!q.empty()) {
        auto entry = q.front();
        q.pop();

        if (!entry.second) {
            auto i = entry.first;
            rep(j, 0, m) {
                if (!vis_col[j]) {
                    col_cnt[j].first -= b[i][j];
                    col_cnt[j].second--;
                    if (col_cnt[j].first == col_cnt[j].second) {
                        vis_col[j] = true;
                        q.push({j, true});
                    }
                }
            }
        } else {
            auto j = entry.first;
            rep(i, 0, n) {
                if (!vis_row[i]) {
                    row_cnt[i].first -= b[i][j];
                    row_cnt[i].second--;
                    if (row_cnt[i].first == 0) {
                        vis_row[i] = true;
                        q.push({i, false});
                    }
                }
            }
        }
    }

    rep(i, 0, n) {
        rep(j, 0, m) {
            if (!vis_row[i] && !vis_col[j] && a[i][j] != b[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector a(n, vector(m, 0));
    vector b(n, vector(m, 0));
    rep(i, 0, n) {
        rep(j, 0, m) {
             cin >> a[i][j];
        }
    }
    rep(i, 0, n) {
        rep(j, 0, m) {
             cin >> b[i][j];
        }
    }

    rep(p, 0, 30) {
        vector a_bit(n, vector(m, 0));
        vector b_bit(n, vector(m, 0));
        rep(i, 0, n) {
            rep(j, 0, m) {
                a_bit[i][j] = ((a[i][j] >> p) & 1);
                b_bit[i][j] = ((b[i][j] >> p) & 1);
            }
        }

        if (!works(a_bit, b_bit)) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
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
