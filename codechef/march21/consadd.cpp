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

void solve() {
    int r, c, x;
    cin >> r >> c >> x;
    vector<vector<ll>> grid(r, vector<ll>(c));
    vector<ll> cnt_1(x);
    vector<ll> cnt_2(x);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int y; cin >> y;
            cnt_1[(i + j) % x] += grid[i][j] - y;
            cnt_2[(i % x - j % x + x) % x] += grid[i][j] - y;
        }
    }

    for (int i = 0; i < x; i++) {
        if (cnt_1[i] != cnt_1[0] || cnt_2[i] != cnt_2[0]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
