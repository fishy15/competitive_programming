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
#define MAXN 1000000

using namespace std;

int n, sz;
string s;
int nxt[101][26];
int suf[101];
int dp[1001][101];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    cin >> s;
    sz = s.size();

    nxt[0][s[0] - 'A'] = 1;

    for (int i = 1; i < sz; i++) {
        suf[i] = nxt[suf[i - 1]][s[i] - 'A'];
        for (int c = 0; c < 26; c++) {
            if (s[i] - 'A' == c) {
                nxt[i][c] = i + 1;
            } else {
                nxt[i][c] = nxt[suf[i - 1]][c];
            }
        }
    }

    dp[0][0] = 1;

    for (int i = 0; i < n; i++) {
        for (int m = 0; m < sz; m++) {
            for (int c = 0; c < 26; c++) {
                int &x = dp[i + 1][nxt[m][c]];
                x += dp[i][m];
                if (x >= MOD) x -= MOD;
            }
        }
        dp[i + 1][sz] += (ll) dp[i][sz] * 26 % MOD;
        if (dp[i + 1][sz] >= MOD) dp[i + 1][sz] -= MOD;
    }

    cout << dp[n][sz] << '\n';

    return 0;
}
