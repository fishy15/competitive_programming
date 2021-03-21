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

ll cnt(ll x, ll y) {
    ll ans = 0;
    ans += min(x, y / 2);
    ans += min(x / 2, y);
    if (x >= 1 && y >= 2) ans--;
    if (x >= 2 && y >= 1) ans--;
    return ans;
}

void solve() {
    int r, c; cin >> r >> c;
    vector<vector<int>> grid(r, vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }

    vector<vector<int>> left(r, vector<int>(c));
    vector<vector<int>> right(r, vector<int>(c));
    vector<vector<int>> top(r, vector<int>(c));
    vector<vector<int>> bot(r, vector<int>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (j > 0) left[i][j] += left[i][j - 1];
            if (grid[i][j]) {
                left[i][j]++;
            } else {
                left[i][j] = 0;
            }
        }

        for (int j = c - 1; j >= 0; j--) {
            if (j < c - 1) right[i][j] += right[i][j + 1];
            if (grid[i][j]) {
                right[i][j]++;
            } else {
                right[i][j] = 0;
            }
        }
    }

    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            if (i > 0) top[i][j] += top[i - 1][j];
            if (grid[i][j]) {
                top[i][j]++;
            } else {
                top[i][j] = 0;
            }
        }

        for (int i = r - 1; i >= 0; i-- ) {
            if (i < r - 1) bot[i][j] += bot[i + 1][j];
            if (grid[i][j]) {
                bot[i][j]++;
            } else {
                bot[i][j] = 0;
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j]) {
                ans += cnt(top[i][j], right[i][j]);
                ans += cnt(top[i][j], left[i][j]);
                ans += cnt(bot[i][j], right[i][j]);
                ans += cnt(bot[i][j], left[i][j]);
            }
        }
    }

    cout << ans << '\n';
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
