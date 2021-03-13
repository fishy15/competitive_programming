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
    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int start = 0;
    if (n % 3 == 0) start = 1;
    for (int i = start; i < n; i += 3) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = 'X';
        }
        if (i + 3 < n) {
            bool done = false;
            for (int j = 0; j < m; j++) {
                if (grid[i + 1][j] == 'X' || grid[i + 2][j] == 'X') {
                    grid[i + 1][j] = 'X';
                    grid[i + 2][j] = 'X';
                    done = true;
                    break;
                }
            }
            if (!done) {
                grid[i + 1][0] = 'X';
                grid[i + 2][0] = 'X';
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
