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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    vector max_diff(n, vector(n, INF));
    rep(i, 0, n) {
        max_diff[i][i] = 0;
    }
    rep(i, 0, m) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;
        ckmin(max_diff[y][x], z);
    }

    auto min_diff = max_diff;
    rep(k, 0, n) {
        rep(i, 0, n) {
            rep(j, 0, n) {
                ckmin(min_diff[i][j], min_diff[i][k] + min_diff[k][j]);
            }
        }
    }

    int q;
    cin >> q;

    while (q--) {
        int k;
        cin >> k;

        vector<int> a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }

        rep(cur, 0, n) {
            int cur_min = INF;
            int cur_max = INF;
            rep(i, 0, n) {
                ckmin(cur_max, a[i] + max_diff[i][cur]);
                ckmin(cur_min, a[i] + min_diff[i][cur]);
            }

            bool unstable = (cur_min != cur_max);
            rep(i, 0, n) {
                auto new_max = min(cur_max, a[i] + max_diff[i][cur] - k);
                auto new_min = min(cur_min, a[i] + min_diff[i][cur] - k);
                if (new_max != new_min) {
                    unstable = true;
                    break;
                }
            }

            cout << unstable;
        }
        cout << '\n';
    }

    return 0;
}
