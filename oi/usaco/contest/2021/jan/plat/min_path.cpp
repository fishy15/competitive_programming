#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#define ll long long
#define INFLL 0x3f3f3f3f
#define MAXN 2010

using namespace std;

int n, m;
ll c[200010];
ll dp[MAXN][MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> c[i];
    }

    if (n <= 2000 && m <= 2000) {
        memset(dp, 0x3f, sizeof dp);
        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + (i + 1) * (i + 1));
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + c[j]);
            }
        }

        int q; cin >> q;
        while (q--) {
            int a, b; cin >> a >> b;
            a--; b--;
            cout << dp[a][b] << '\n';
        }
    } else {
        int q; cin >> q;
        while (q--) {
            ll a, b; cin >> a >> b;
            a--; b--;
            ll l = 0;
            ll r = a;
            ll ans;
            auto calc = [&](const ll x) { return c[0] * x + ((x + 1) * (x + 1)) * b + c[b] * (a - x); };
            while (l < r + 3) {
                ll m1 = l + (r - l) / 3;
                ll m2 = r - (r - l) / 3;
                ll v1 = calc(m1);
                ll v2 = calc(m2);
                if (v1 < v2) {
                    r = m2 - 1;
                    ans = v1;
                } else if (v1 == v2) {
                    l = m1 + 1;
                    r = m2 - 1;
                    ans = v2;
                } else {
                    l = m1 + 1;
                    ans = v2;
                }
            }

            for (int i = l; i <= r; i++) {
                ans = min(ans, calc(i));
            }

            cout << ans << '\n';
        }
    }

    return 0;
}
