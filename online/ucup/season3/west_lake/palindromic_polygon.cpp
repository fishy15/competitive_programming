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

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    T cross(P p) const { return x*p.y - y*p.x; } // + => p on right
};

using P = Point<ll>;

template<typename T>
T &ckmax(T &a, T b) {
    return a = max(a, b);
}

void solve() {
    int n;
    cin >> n;

    vector<int> v(2 * n);
    rep(i, 0, n) {
        cin >> v[i];
        v[i + n] = v[i];
    }

    vector<P> poly(2 * n);
    rep(i, 0, n) {
        P p;
        cin >> p.x >> p.y;
        poly[i] = poly[i + n] = p;
    }

    // dp[start][end][0] = both have been matched
    // dp[start][end][1] = one end is unmatched
    vector dp(2*n, vector<array<ll, 2>>(2*n, {-INFLL, -INFLL}));
    ll ans = 0;
    for (int start = 2*n-1; start >= 0; start--) {
        rep(end, start, min(start+n, 2*n)) {
            if (v[start] == v[end]) {
                ckmax(dp[start][end][0], poly[start].cross(poly[end]));
                auto area = dp[start][end][0] + poly[end].cross(poly[start]);
                ckmax(ans, area);

                // try extending start backwards
                for (int new_start = start-1; new_start >= 0; new_start--) {
                    if (end-new_start >= n) {
                        break;
                    }
                    ckmax(dp[new_start][end][1], dp[start][end][0] + poly[new_start].cross(poly[start]));
                }
            }

            // try extending forward
            rep(new_end, end+1, min(start+n, 2*n)) {
                if (v[start] == v[new_end]) {
                    ckmax(dp[start][new_end][0], dp[start][end][1] + poly[end].cross(poly[new_end]));
                }
            }
        }
    }

    cout << ans << '\n';
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
