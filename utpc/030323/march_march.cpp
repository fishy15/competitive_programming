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

template<typename T>
T &ckmin(T &a, T b) {
    return a = min(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m;
    cin >> n >> m;

    int c, d;
    cin >> c >> d;

    vector<bool> adj(n * n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a * n + b] = true;
    }

    vector<int> digits(1 << n);
    for (int i = 1; i < (1 << n); i++) {
        digits[i] = digits[i / 2] + (i & 1);
    }

    vector cur_dp(n, vector<int>(1 << n, INF));

    for (int j = 0; j < (1 << n); j++) {
        for (int v = 0; v < n; v++) {
            for (int nxt = 0; nxt < n; nxt++) {
                if (j & (1 << nxt)) continue;

                int needed = digits[j];
                int cost_build = adj[v * n + nxt] ? 0 : c;
                int cost_conv = nxt >= needed ? 0 : d;

                if (j == 0) {
                    if (nxt == 0) {
                        cur_dp[nxt][1 << nxt] = 0;
                    } else {
                        cur_dp[nxt][1 << nxt] = d;
                    }
                } else {
                    ckmin(cur_dp[nxt][j ^ (1 << nxt)], cur_dp[v][j] + cost_build + cost_conv);
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < n; i++) {
        ckmin(ans, cur_dp[i][(1 << n) - 1]);
    }

    cout << ans << '\n';

    return 0;
}
