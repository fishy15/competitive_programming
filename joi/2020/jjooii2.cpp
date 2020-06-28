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

#define ll long long
#define eps 1e-8
#define MOD 1000000007

#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f

// change if necessary
#define MAXN 200010

using namespace std;

int n, k;
string s;
int dp[MAXN][3];
int jrem[MAXN];
int irem[MAXN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> k;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        switch (s[i - 1]) {
            case 'J':
                dp[i][0]++;
                break;
            case 'O':
                dp[i][1]++;
                break;
            case 'I':
                dp[i][2]++;
                break;
        }
        dp[i][0] += dp[i - 1][0];
        dp[i][1] += dp[i - 1][1];
        dp[i][2] += dp[i - 1][2];
    }

    queue<int> j;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == 'J') {
            j.push(i);
            if (j.size() > k) j.pop();
        }
        if (j.size() == k) jrem[i] = j.front();
    }

    queue<int> ii;
    for (int i = n; i >= 1; i--) {
        if (s[i - 1] == 'I') {
            ii.push(i);
            if (ii.size() > k) ii.pop();
        }
        if (ii.size() == k) irem[i] = ii.front();
    }

    int l = 1;
    int r = 1;
    int ans = INF;
    while (l <= n) {
        while (l <= n && !jrem[l]) {
            l++;
            if (r < l) r++;
        }

        while (r <= n && dp[r][1] - dp[l][1] < k) r++;
        if (!irem[r + 1]) break;
        ans = min(ans, n - 3 * k - jrem[l] + 1 - (n - irem[r + 1]));
        l++;
    }

    if (ans == INF) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}
