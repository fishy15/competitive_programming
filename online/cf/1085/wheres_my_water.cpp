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
    int n;
    ll h;
    cin >> n >> h;

    vector<ll> a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << h - a[0] << '\n';
        return;
    }

    vector max_from(n, vector<ll>(n));
    vector<ll> get_left(n);
    vector<ll> get_right(n);
    rep(st, 0, n) {
        max_from[st][st] = a[st];
        get_left[st] = get_right[st] = a[st];
        for (int j = st - 1; j >= 0; j--) {
            max_from[st][j] = max(a[j], max_from[st][j+1]);
            get_left[st] += max_from[st][j];
        }
        for (int j = st + 1; j < n; j++) {
            max_from[st][j] = max(a[j], max_from[st][j-1]);
            get_right[st] += max_from[st][j];
        }
    }

    vector max_from_psum(n, vector<ll>(n+1));
    rep(i, 0, n) {
        rep(j, 0, n) {
            max_from_psum[i][j+1] = max_from_psum[i][j] + max_from[i][j];
        }
    }

    ll ans = n*h;
    rep(i, 0, n) {
        rep(j, i+1, n) {
            auto cur = get_left[i] + get_right[j]; 
            if (j - i - 1 > 0) {
                int ans = j;
                int lo = i + 1;
                int hi = j - 1;
                while (lo <= hi) {
                    int m = (lo + hi) / 2;
                    if (max_from[i][m] > max_from[j][m]) {
                        ans = m;
                        hi = m - 1;
                    } else {
                        lo = m + 1;
                    }
                }

                // (i, m) belongs to i
                // [m, j) belongs to j
                cur += max_from_psum[i][ans] - max_from_psum[i][i+1];
                cur += max_from_psum[j][j] - max_from_psum[j][ans];
            }
            ans = min(ans, cur);
        }
    }

    cout << n * h - ans << '\n';
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
