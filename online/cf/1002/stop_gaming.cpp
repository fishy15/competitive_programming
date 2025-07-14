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

    vector a(n, vector<int>(m));
    vector b(n, vector<int>(m));
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

    int pref = 0;
    int last_could_move = 0;
    rep(i, 0, n) {
        rep(j, 0, m) {
            auto x = pref / m;
            auto y = pref % m;

            auto can_move = (y == 0) || (i != x);
            if (can_move) {
                last_could_move = pref;
            }

            if (a[x][y] == b[i][j]) {
                pref++;
            } else if (!can_move) {
                // no way to fix the element after pref
                pref = last_could_move;
                goto end;
            }
        }
    }

end:
    cout << n * m - pref << '\n';
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
