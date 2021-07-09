/*
 * Note that each diagonal from the top right to bottom left must have the same character. This is because we
 * can construct paths that only differ at one point in a diagonal, and so they must have the same character
 * there. Therefore, we reduce the problem to finding the kth balanced bracket string according to the lowest
 * priority for each diagonal. This can be done by going in order of the priorities and counting how many 
 * balanced bracket strings exist with '(' in that position, and if less than k, then using ')' instead.
 */
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
#define INFLL 0x3f3f3f3f3f3f3f3fLL

// change if necessary
#define MAXN 110

using namespace std;

int n, m;
ll k;
int p[MAXN * 2];
string s;

ll dp[MAXN * 2][MAXN * 2];

ll count() {
    memset(dp, 0, sizeof dp);
    if (s[0] == ')') return 0;
    dp[0][1] = 1;
    for (int i = 1; i < n + m - 1; i++) {
        if (s[i] != ')') {
            for (int j = 1; j < n + m - 1; j++) {
                dp[i][j] += dp[i - 1][j - 1];
                dp[i][j] = min(dp[i][j], INFLL);
            }
        }

        if (s[i] != '(') {
            for (int j = 0; j < n + m - 2; j++) {
                dp[i][j] += dp[i - 1][j + 1];
                dp[i][j] = min(dp[i][j], INFLL);
            }
        }
    }

    return dp[n + m - 2][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m >> k;
    k--;
    
    fill(p, p + n + m - 1, INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            p[i + j] = min(p[i + j], x);
        }
    }

    s = string(n + m - 1, '?');
    vector<pair<int, int>> pos;
    for (int i = 0; i < n + m - 1; i++) {
        pos.push_back({p[i], i});
    }

    sort(pos.begin(), pos.end());

    for (auto [priority, idx] : pos) {
        s[idx] = '(';
        ll cnt = count();
        if (k >= cnt) {
            k -= cnt;
            s[idx] = ')';
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << s[i + j];
        }
        cout << '\n';
    }

    return 0;
}
