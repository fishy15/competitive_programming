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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<ll> p(n);
    vector<ll> d(n);
    vector<ll> ppsum(n+1);
    vector<ll> dpsum(n+1);
    rep(i, 0, n) {
        cin >> p[i];
        ppsum[i+1] = ppsum[i] + p[i];
    }
    rep(i, 0, n) {
        cin >> d[i];
        dpsum[i+1] = dpsum[i] + d[i];
    }

    ld ans = 0;
    auto solve = [&](auto &&self, int l, int r) -> void {
        if (l > r) return;
        if (l == r) {
            ans = max(ans,(ld) p[l] * p[l] / d[l]);
        } else {
            int m = (l + r) / 2;
            auto solve2 = [&](auto &&self, int Ll, int Lr, int Rl, int Rr) -> void {
                if (Ll > Lr) return;
                int Lm = (Ll + Lr) / 2;
                pair<ld, int> best;
                for (int j = Rl; j <= Rr; j++) {
                    ld ps = ppsum[j+1] - ppsum[Lm];
                    ld ds = dpsum[j+1] - dpsum[Lm];
                    best = max(best, {ps * ps / ds, j});
                }
                ans = max(ans, best.first);
                self(self, Ll, Lm-1, best.second, Rr);
                self(self, Lm+1, Lr, Rl, best.second);
            };
            solve2(solve2, l, m, m, r);
            self(self, l, m-1);
            self(self, m+1, r);
        }
    };
    solve(solve, 0, n-1);

    cout << fixed << setprecision(15);
    cout << ans << '\n';

    return 0;
}
