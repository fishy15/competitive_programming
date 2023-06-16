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

#define ll long long
#define ld long double
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

string ord = "0123456789ABCDEF";
string n;
int len;
int k;
ll ans;

ll dp[MAXN][20][2];
// solve for exactly k digits
// same # of digits as n, <= n
ll solve(string &n, int k) {
    memset(dp, 0, sizeof dp);

    int len = n.size();

    // set init dig
    for (int i = 1; i < 16; i++) {
        if (ord[i] == n[0]) {
            dp[0][1][1] = 1;
            break;
        } else {
            dp[0][1][0]++;
        }
    }

    dp[0][0][0] = 1;

    set<int> cur = {n[0]};
    for (int i = 1; i < len; i++) {
        // transition from match
        for (int j = 0; j < 16; j++) {
            if (ord[j] == n[i]) {
                int cur_sz = cur.size();
                int nxt_sz = cur.size();
                if (!cur.count(ord[j])) nxt_sz++;
                ll &val = dp[i][nxt_sz][1] += dp[i - 1][cur_sz][1];
                if (val >= MOD) val -= MOD;
                cur.insert(ord[j]);
                break;
            } else {
                int cur_sz = cur.size();
                int nxt_sz = cur.size();
                if (!cur.count(ord[j])) nxt_sz++;
                ll &val = dp[i][nxt_sz][0] += dp[i - 1][cur_sz][1];
                if (val >= MOD) val -= MOD;
            }
        }

        // unmatched part
        for (int j = 0; j <= k; j++) {
            int opt = j;
            if (j == 0) opt = 1;
            ll &val = dp[i][j][0] += dp[i - 1][j][0] * opt % MOD;
            if (val >= MOD) val -= MOD;
            int rest = 16 - opt;
            ll &val2 = dp[i][j + 1][0] += dp[i - 1][j][0] * rest % MOD;
            if (val2 >= MOD) val2 -= MOD;
        }
    }

    return (dp[len - 1][k][0] + dp[len - 1][k][1]) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    ll ans = solve(n, k);

    cout << ans << '\n';

    return 0;
}
