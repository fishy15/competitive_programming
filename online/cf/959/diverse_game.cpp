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

void solve() {
    int n, m;
    cin >> n >> m;

    vector grid(n, vector<int>(m));
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> grid[i][j];
        }
    }

    if (n * m == 1) {
        cout << "-1\n";
    } else {
        rep(i, 0, n) {
            rep(j, 0, m) {
                if (grid[i][j] == n*m) {
                    grid[i][j] = 1;
                } else {
                    grid[i][j]++;
                }
                cout << grid[i][j] << ' ';
            }
            cout << '\n';
        }
        
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
