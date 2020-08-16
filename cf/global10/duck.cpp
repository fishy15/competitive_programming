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

int n;
ll grid[25][25];

ll minpath(int x, int y) {
    ll ans = 0;
    while (x != n - 1 || y != n - 1) {
        ans += grid[x][y];
        if (x < n - 1) {
            x++; 
        } else {
            y++;
        }
    }
    return ans;
}

ll maxpath(int x, int y) {
    ll ans = 0;
    while (x != n - 1 || y != n - 1) {
        ans += grid[x][y];
        if (y < n - 1) {
            y++; 
        } else {
            x++;
        }
    }
    return ans;
}

void solve() {
    int x = 0;
    int y = 0;
    vector<pair<int, int>> ans = {{1, 1}};
    ll num; cin >> num;
    while (x != n - 1 || y != n - 1) {
        num -= grid[x][y];
        if (x == n - 1) {
            y++;
        } else if (y == n - 1) {
            x++;
        } else {
            if (num <= maxpath(x + 1, y)) {
                x++;
            } else {
                y++;
            }
        }
        ans.push_back({x + 1, y + 1});
    }
    for (auto p : ans) {
        cout << p.first << ' ' << p.second << endl;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            ll val = maxpath(i + 1, j) - minpath(i, j + 1) + 1;
            grid[i][j + 1] = val;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }

    int q; cin >> q;
    while (q--) solve();

    return 0;
}
