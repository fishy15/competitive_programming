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
    int n, m; cin >> n >> m;
    vector<string> grid;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        grid.push_back(s);
    }

    // last col
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += grid[i][m - 1] == 'R';
    }

    for (int i = 0; i < m; i++) {
        ans += grid[n - 1][i] == 'D';
    }

    cout << ans << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
