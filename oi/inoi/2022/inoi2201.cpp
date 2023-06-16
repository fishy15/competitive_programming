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
#define MAXN 30010
#define MAXM 1010

using namespace std;

int n, m;
int a[MAXN];
array<int, 3> b[MAXM];
ll dp[MAXN][MAXM];

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

void subtask5() {
    // just give everything its best option
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int loc = a[i];
        auto it = upper_bound(b, b + m, loc, [&](int value, const array<int, 3> &element) {
            return value < element[0];
        });

        ll x = INFLL;
        if (it != b + m) {
            x = min(x, abs((ll)(*it)[0] - loc));
        }

        if (it != b) {
            it--;
            x = min(x, abs((ll)(*it)[0] - loc));
        }

        ans += x;
    }

    cout << ans << '\n';
}

void subtask7() {
    // greedily assign everything 
    int cur = 0;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < b[i][1]; j++) {
            ans += abs((ll) a[cur] - b[i][0]);
            cur++;
        }
    }

    cout << ans << '\n';
}

ll get_sum(int l, int r, ll loc) {
    ll ans = 0;
    for (int i = l; i < r; i++) {
        ans += abs(loc - a[i]);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);

    ll s_sum = 0;
    ll e_sum = 0;
    bool st5 = true;
    bool st7 = true;
    for (int i = 0; i < m; i++) {
        cin >> b[i][0] >> b[i][1] >> b[i][2];
        s_sum += b[i][1];
        e_sum += b[i][2];

        if (b[i][1] != 0 || b[i][2] != n) {
            st5 = false;
        }

        if (b[i][1] != b[i][2]) {
            st7 = false;
        }
    }

    sort(b, b + m);

    if (s_sum > n || e_sum < n) {
        cout << "-1\n";
        return 0;
    }

    if (st5) {
        subtask5();
        return 0;
    }

    if (st7) {
        subtask7();
        return 0;
    }

    // do regular dp
    memset(dp, 0x3f, sizeof dp);
    for (int i = 0; i < m; i++) {
        auto [loc, s, e] = b[i];
        for (int st = 0; st + s <= n; st++) {
            ll sum = get_sum(st, st + s, loc);
            for (int j = s; j <= e && st + j <= n; j++) {
                ll prev = i > 0 ? dp[i - 1][st] : (st == 0 ? 0 : INFLL);
                ckmin(dp[i][st + j], prev + sum);
                if (st + j < n) sum += abs((ll) loc - a[st + j]);
            }
        }
    }

    if (dp[m - 1][n] == INFLL) {
        cout << "-1\n";
    } else {
        cout << dp[m - 1][n] << '\n';
    }

    return 0;
}
