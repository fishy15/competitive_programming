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

// change if necessary
#define MAXN 1000000

using namespace std;

template<class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); }
};

using P = Point<ll>;

ld tsp(const vector<vector<ld>> &grid) {
    int n = grid.size();

    vector dp(1 << n, vector<ld>(n, INFLL));
    dp[0].assign(n, 0);

    for (int m = 0; m < (1 << n); m++) {
        for (int p = 0; p < n; p++) {
            for (int v = 0; v < n; v++) {
                if ((m & (1 << v)) == 0) {
                    int nxt_m = m ^ (1 << v);
                    dp[nxt_m][v] = min(dp[nxt_m][v], dp[m][p] + grid[p][v]);
                }
            }
        }
    }

    return *min_element(dp.back().begin(), dp.back().end());
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<P> pts(n);
    for (auto &p : pts) {
        cin >> p.x >> p.y;
    }

    auto comp = [&](ld ang) {
        vector dist(n, vector<ld>(n));

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                auto vec = pts[i] - pts[j];
                auto diam = vec.dist();
                auto theta = vec.angle() - ang;
                auto d = diam * (abs(sin(theta)) + abs(cos(theta)));
                dist[i][j] = dist[j][i] = d;
            }
        }

        return tsp(dist);
    };

    ld ans = INFLL;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            auto ang = (pts[i] - pts[j]).angle();
            ans = min(ans, comp(ang));
        }
    }

    cout << fixed << setprecision(20);
    cout << ans << '\n';

    return 0;
}
