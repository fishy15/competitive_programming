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

constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;

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

    int n, s, e;
    cin >> n >> s >> e;
    s--;
    e--;

    vector<ll> x(n), a(n), b(n), c(n), d(n);
    rep(i, 0, n) {
        cin >> x[i];
    }
    rep(i, 0, n) {
        cin >> a[i];
    }
    rep(i, 0, n) {
        cin >> b[i];
    }
    rep(i, 0, n) {
        cin >> c[i];
    }
    rep(i, 0, n) {
        cin >> d[i];
    }

    vector dp(n+1, vector(n+1, INFLL));

    auto leave_left = [&](int i) {
        return c[i] + x[i];
    };
    auto leave_right = [&](int i) {
        return d[i] - x[i];
    };
    auto come_left = [&](int i) {
        return a[i] + x[i];
    };
    auto come_right = [&](int i) {
        return b[i] - x[i];
    };
    
    if (s == 0) {
        dp[1][1] = leave_right(0);
    } else if (e == 0) {
        dp[1][1] = come_right(0);
    } else {
        dp[1][1] = come_right(0) + leave_right(0);
    }

    rep(i, 1, n) {
        rep(cc, 1, n+1) {
            if (i == s) {
                // creating a new component
                if (cc < n) {
                    ckmin(dp[i+1][cc+1], dp[i][cc] + leave_right(i));
                }

                // attaching to left side of a component
                ckmin(dp[i+1][cc], dp[i][cc] + leave_left(i));
            } else if (i == e) {
                // creating a new component
                if (cc < n) {
                    ckmin(dp[i+1][cc+1], dp[i][cc] + come_right(i));
                }

                // attaching to the right side of a component
                ckmin(dp[i+1][cc], dp[i][cc] + come_left(i));
            } else {
                // create a new component
                if (cc < n && (cc + 1) - (i > s) - (i > e) > 0) {
                    ckmin(dp[i+1][cc+1], dp[i][cc] + come_right(i) + leave_right(i));
                }

                // attach to left side of a component
                if (cc - (i > s) > 0) {
                    ckmin(dp[i+1][cc], dp[i][cc] + come_right(i) + leave_left(i));
                }

                // attach to the right side of a component
                if (cc - (i > e) > 0) {
                    ckmin(dp[i+1][cc], dp[i][cc] + come_left(i) + leave_right(i));
                }

                // join two components
                if (cc > 1) {
                    ckmin(dp[i+1][cc-1], dp[i][cc] + come_left(i) + leave_left(i));
                }
            }
        }
    }

    cout << dp[n][1] << '\n';

    return 0;
}
